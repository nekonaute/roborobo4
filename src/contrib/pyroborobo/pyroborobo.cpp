//
// Created by pecoffet on 05/06/2020.
//



#include <csignal>
#include <core/Config/GlobalConfigurationLoader.h>
#include <RoboroboMain/roborobo.h>

#include "Utilities/Graphics.h"
#include "RoboroboMain/main.h"
#include "Controllers/Controller.h"
#include "contrib/pyroborobo/ControllerTrampoline.h"
#include "contrib/pyroborobo/RobotWorldModelTrampoline.h"
#include "World/World.h"
#include "contrib/pyroborobo/PyConfigurationLoader.h"
#include <pybind11/pybind11.h>

#include <pybind11/stl.h>
#include <contrib/pyroborobo/pyroborobo.h>

#include <contrib/pyroborobo/PyPhysicalObjectFactory.h>


namespace py = pybind11;
using namespace pybind11::literals;

std::shared_ptr<Pyroborobo> Pyroborobo::instance = nullptr;


std::shared_ptr<Pyroborobo> Pyroborobo::createRoborobo(const std::string &properties_file, py::object worldObserverClass,
                                       py::object agentControllerClass, py::object worldModelClass,
                                       py::object agentObserverClass, py::dict objectClassDict,
                                       const py::dict options)
{
    if (instance != nullptr)
    {
        throw std::runtime_error("Pyroborobo has already been instantiated");
    }
    instance = std::make_shared<Pyroborobo>(properties_file, worldObserverClass, agentControllerClass, worldModelClass,
                              agentObserverClass, objectClassDict, options);
    return instance;
}

std::shared_ptr<Pyroborobo> Pyroborobo::get()
{
    if (instance == nullptr)
    {
        throw std::runtime_error("Pyroborobo has not been created");
    }
    return instance;
}


Pyroborobo::Pyroborobo(const std::string &properties_file,
                       py::object worldObserverClass,
                       py::object agentControllerClass,
                       py::object worldModelClass,
                       py::object agentObserverClass,
                       py::dict objectClassDict,
                       const py::dict options)
        :
        currentIt(0),
        worldObserverClass(worldObserverClass),
        agentControllerClass(agentControllerClass),
        worldModelClass(worldModelClass),
        agentObserverClass(agentObserverClass)
{
    bool success = loadPropertiesFile(properties_file);
    if (!success)
    {
        throw std::runtime_error(
                "Impossible to load the property files. Did you provide the correct path? Does your config file contains errors?");
    }
    this->overrideProperties(options);
    for (auto elem : objectClassDict)
    {
        if (!py::isinstance<py::str>(elem.first))
        {
            throw std::runtime_error("object key in objet_class_dict is not a string");
        }
        this->objectClassDict[elem.first.cast<std::string>()] = elem.second;
    }
}

void Pyroborobo::start()
{
    loadProperties(); /* file has already been loaded in constructor */
    PyPhysicalObjectFactory::init();
    py::handle objectClass = py::none();
    if (objectClassDict.find("_default") != objectClassDict.end())
    {
        objectClass = objectClassDict["_default"];
    }
    /* TODO move init to start */
    this->initCustomConfigurationLoader(worldObserverClass, agentControllerClass,
                                        worldModelClass, agentObserverClass);
    PyPhysicalObjectFactory::updateObjectConstructionDict(objectClassDict);

    currentIt = 0;


    signal(SIGINT, quit);
    signal(SIGTERM, quit);

    /* Taken from init Roborobo */
    gCamera.x = 0;
    gCamera.y = 0;
    gCamera.w = gArenaWidth;
    gCamera.h = gArenaHeight;

    if (!initSDL(SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE))
    {
        py::print("[CRITICAL] cannot initialize SDL: ", SDL_GetError());
        exit(-2);
    }

    // * Initialize log file(s)

    initLogging();


    // * Initialize Random seed -- loaded, or initialized, in loadProperties(...)

    engine.seed(gRandomSeed);

    //srand(gRandomSeed); // fixed seed - useful to reproduce results (ie. deterministic sequence of random values)
    //gLogFile << "# random seed             : " << gRandomSeed << std::endl;

    world = new World();
    gWorld = world;

    // * run

    world->initWorld([=]() {this->_gatherProjectInstances();});


    if (!gBatchMode)
    {
        initMonitor(true);
    } // add speed monitoring and inspector agent

}

bool Pyroborobo::update(size_t n_step)
{
    if (gWorld == nullptr)
    {
        throw std::runtime_error("No Environment. Did you forget to call rob.start()?");
    }
    bool quit = false;
    size_t i = 0;
    while (i < n_step && !quit) /* i++ after update if not pausemode */
    {
        if (gBatchMode)
        {
            gWorld->updateWorld();
            i++;
            if (gWorld->getIterations() % 10000 == 0)
            {
                if (gVerbose)
                {
                    std::cout << ".";
                }
            }

            // monitor trajectories (if needed)
            if (gTrajectoryMonitor)
                updateTrajectoriesMonitor();
        }
        else
        {
            const Uint8 *keyboardStates = SDL_GetKeyboardState(nullptr);
            quit = checkEvent() | handleKeyEvent(keyboardStates);

            //Start the frame timer
            fps.start();
            if (!gPauseMode)
            {
                if (gUserCommandMode && !gInspectorMode)
                    gWorld->updateWorld(keyboardStates);
                else
                    gWorld->updateWorld();
                i++;
            }
            //Update the screen
            updateDisplay();

            // monitor trajectories (if needed)
            if (gTrajectoryMonitor)
                updateTrajectoriesMonitor();

            updateMonitor(keyboardStates);
        }

        currentIt++;
        if (gWorld->getNbOfRobots() <= 0)
        {
            quit = true;
        }
    }
    return quit;
}

const std::vector<py::object > & Pyroborobo::getControllers() const
{
    if (!initialized)
    {
        throw std::runtime_error("Controllers have not been instanciated yet. Have you called roborobo.start()?");
    }
    return controllers;
}

const std::vector<py::object > & Pyroborobo::getWorldModels() const
{
    if (!initialized)
    {
        throw std::runtime_error("World models have not been instantiated yet. Have you called roborobo.start()?");
    }
    return worldmodels;
}

const std::vector<py::object > & Pyroborobo::getAgentObservers() const
{
    if (!initialized)
    {
        throw std::runtime_error(
                "Agent Observers have not been instantiated yet. Have you called roborobo.start()?");
    }
    return agentobservers;
}


const std::vector<py::object > & Pyroborobo::getObjects() const
{
    if (!initialized)
    {
        throw std::runtime_error("Objects have not been instantiated yet. Have you called roborobo.start()?");
    }
    return objects;
}


void Pyroborobo::close()
{
    gConfigurationLoader = nullptr;
    PyPhysicalObjectFactory::close();
    closeRoborobo();
    controllers.clear();
    worldmodels.clear();
    agentobservers.clear();
    objects.clear();
    landmarks.clear();
    pywobs = py::none();

    delete gConfigurationLoader;
}

void Pyroborobo::_gatherProjectInstances()
{
    size_t nbObj = gPhysicalObjects.size();
    size_t nbLandmarks = gLandmarks.size();

    objects.reserve(nbObj);
    landmarks.reserve(nbLandmarks);

    wobs = world->getWorldObserver();

    for (size_t i = 0; i < nbObj; i++)
    {
        objects.emplace_back(py::cast(gPhysicalObjects[i]));
    }

    for (size_t i = 0; i < nbLandmarks; i++)
    {
        landmarks.emplace_back(py::cast(gLandmarks[i]));
    }
    initialized = true;

}

void Pyroborobo::overrideProperties(const py::dict dict)
{
    for (auto elem : dict)
    {
        gProperties.setProperty(py::str(elem.first).cast<std::string>(), py::str(elem.second).cast<std::string>());
    }
}

void Pyroborobo::initCustomConfigurationLoader(py::object worldObserverClass, py::object agentControllerClass,
                                               py::object worldModelClass, py::object agentObserverClass)
{
    gConfigurationLoader = new PyConfigurationLoader(gConfigurationLoader, worldObserverClass, agentControllerClass,
                                                     worldModelClass, agentObserverClass, *this);
}

py::object Pyroborobo::addObjectToEnv(py::object obj)
{
    auto c_obj = obj.cast<std::shared_ptr<PhysicalObject>>();
    int id = PhysicalObjectFactory::getNextId();
    assert(id == gNbOfPhysicalObjects);
    c_obj->setId(id);
    if (c_obj->isRegistered())
    {
        c_obj->registerObject(); // Force object registration with the correct id
    }
    gPhysicalObjects.emplace_back(c_obj);
    objects.emplace_back(obj);
    gNbOfPhysicalObjects = gPhysicalObjects.size();
    //std::cout << "gNbOfPhysicalObjects: " << gNbOfPhysicalObjects << std::endl;
    //std::cout << "gPhysicalObjects contains:";
    //for (auto& x: gPhysicalObjects)
    //    std::cout << ' ' << x;
    //std::cout << '\n';
    return obj;
}

void Pyroborobo::setWorldObserver(py::object object)
{
    pywobs = object;
}

void Pyroborobo::appendWorldModel(py::object pywm)
{
    worldmodels.emplace_back(pywm);
}

void Pyroborobo::appendAgentObserver(py::object pyao)
{
    agentobservers.emplace_back(pyao);
}

void Pyroborobo::appendController(py::object pyctl)
{
    controllers.emplace_back(pyctl);
}

Pyroborobo::~Pyroborobo() = default;
