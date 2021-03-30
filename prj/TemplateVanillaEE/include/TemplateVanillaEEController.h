/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#ifndef TEMPLATEVANILLAEECONTROLLER_H
#define TEMPLATEVANILLAEECONTROLLER_H

#include "TemplateEE/include/TemplateEEController.h"
#include "Utilities/Packet.h"

using namespace Neural;

class RobotWorldModel;

class TemplateVanillaEEController : public TemplateEEController
{
    public:
    
        TemplateVanillaEEController(std::shared_ptr<RobotWorldModel> wm);

    ~TemplateVanillaEEController();
    
        double getFitness() override;

    protected:
    
        void initController() override;
        void initEvolution() override;
    
        void stepController() override;
        void stepEvolution() override;
    
        void performSelection() override;
        void performVariation() override;
    
        void broadcastGenome() override;

    bool sendGenome(std::shared_ptr<TemplateEEController> __targetRobotController) override;

    bool receiveGenome(Packet *p) override;
    
        void resetFitness() override;
        void updateFitness() override;

        void logCurrentState() override;
};


#endif

