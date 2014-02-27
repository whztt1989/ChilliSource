/*
 *  ParticleComponent.cpp
 *  moFloTest
 *
 *  Created by Scott Downie on 07/01/2011.
 *  Copyright 2011 Tag Games. All rights reserved.
 *
 */

#include <ChilliSource/Rendering/Particles/ParticleComponent.h>

#include <ChilliSource/Rendering/Particles/ParticleSystem.h>
#include <ChilliSource/Rendering/Particles/Effectors/ParticleEffector.h>

namespace ChilliSource
{
	namespace Rendering
	{
        DEFINE_NAMED_INTERFACE(ParticleComponent);
		//=====================================================
		/// Particle Component
		///
		/// Entire particle system
		//=====================================================
		//-----------------------------------------------------
		/// Constructor 
		//-----------------------------------------------------
		ParticleComponent::ParticleComponent(): mpOwningSystem(nullptr), mfUpdateScaleFactor(1.0f), mbEmittersFinished(false)
		{
            SetCullingEnabled(false);
		}
		//----------------------------------------------------------
		/// Is A
		//----------------------------------------------------------
		bool ParticleComponent::IsA(ChilliSource::Core::InterfaceIDType inInterfaceID) const
		{
			return (inInterfaceID == ParticleComponent::InterfaceID) || 
            (inInterfaceID == RenderComponent::InterfaceID);
		}
		//-------------------------------------------------
		/// Set Owning System
		//-------------------------------------------------
		void ParticleComponent::SetOwningSystem(ParticleSystem* inpSystem)
		{
			mpOwningSystem = inpSystem;
		}
		//-------------------------------------------------
		/// Remove From World System
		//-------------------------------------------------
		void ParticleComponent::RemoveFromWorldSystem()
		{
			mpOwningSystem->RemoveParticleComponent(this);
		}
		//---------------------------------------------------
		/// Add Emitter
		//---------------------------------------------------
		void ParticleComponent::AddEmitter(ParticleEmitter* inpEmitter)
		{
            if(inpEmitter)
            {
                mEmitters.push_back(inpEmitter);
            }
		}
		//---------------------------------------------------
		/// Get number of emitters in this system
		//---------------------------------------------------
		u32 ParticleComponent::GetNumEmitters() const
        {
			return mEmitters.size();
		}
		//---------------------------------------------------
		/// Returns the emitter at the given index or nullptr
		//---------------------------------------------------
		ParticleEmitter* ParticleComponent::GetEmitter(u32 inudwIndex){
			
			if (inudwIndex < mEmitters.size())
				return mEmitters[inudwIndex];
				
			return nullptr;
		}
        //---------------------------------------------------
		/// Add Effector
		//---------------------------------------------------
		void ParticleComponent::AddEffector(ParticleEffector* inpEffector)
		{
            if(!inpEffector)
            {
                return;
            }
            
			mEffectors.push_back(inpEffector);
			
            for(std::vector<ParticleEmitter*>::iterator it = mEmitters.begin(); it != mEmitters.end(); ++it)
			{
				(*it)->AddEffector(inpEffector);
			}
		}
		//-------------------------------------------------
		/// Update
		//-------------------------------------------------
		void ParticleComponent::Update(f32 infDt)
		{
            bool bEmittingFinished = true;
            
			for(std::vector<ParticleEmitter*>::iterator it = mEmitters.begin(); it != mEmitters.end(); ++it)
			{
				(*it)->Update(infDt * mfUpdateScaleFactor);
                
                if((*it)->GetIsEmittingFinished() == false)
                {
                    bEmittingFinished = false;
                }
			}
            
            if(bEmittingFinished)
            {
                mbEmittersFinished = true;
            }
		}
        //-------------------------------------------------
        /// Render
        //-------------------------------------------------
        void ParticleComponent::Render(RenderSystem* inpRenderSystem, CameraComponent* inpCam, ShaderPass ineShaderPass)
        {
            if (ineShaderPass == ShaderPass::k_ambient)
            {
                for(std::vector<ParticleEmitter*>::iterator it = mEmitters.begin(); it != mEmitters.end(); ++it)
                {
                    (*it)->Render(inpRenderSystem, inpCam);
                }
            }
        }
        //---------------------------------------------------
        /// Start Emitting
        //---------------------------------------------------
        void ParticleComponent::StartEmitting()
        {
            for(std::vector<ParticleEmitter*>::iterator it = mEmitters.begin(); it != mEmitters.end(); ++it)
			{
				(*it)->StartEmitting();
			}
        }
		//---------------------------------------------------
		/// Emit Once
		//---------------------------------------------------
        void ParticleComponent::EmitBurst()
        {
            for(std::vector<ParticleEmitter*>::iterator it = mEmitters.begin(); it != mEmitters.end(); ++it)
			{
				(*it)->EmitBurst();
			}
        }
        //---------------------------------------------------
        /// Stop Emitting
        //---------------------------------------------------
        void ParticleComponent::StopEmitting()
        {
            for(std::vector<ParticleEmitter*>::iterator it = mEmitters.begin(); it != mEmitters.end(); ++it)
			{
				(*it)->StopEmitting();
			}
        }
        //---------------------------------------------------
        /// Set Update Scale Factor
        //---------------------------------------------------
        void ParticleComponent::SetUpdateScaleFactor(f32 infScale)
        {
            mfUpdateScaleFactor = infScale;
        }
        //-----------------------------------------------------
		/// Destructor 
		//-----------------------------------------------------
		ParticleComponent::~ParticleComponent()
		{
            for(std::vector<ParticleEmitter*>::iterator it = mEmitters.begin(); it != mEmitters.end(); ++it)
			{
				CS_SAFE_DELETE(*it);
			}
			
			for(std::vector<ParticleEffector*>::iterator itEffector = mEffectors.begin(); itEffector != mEffectors.end(); ++itEffector)
            {
                CS_SAFE_DELETE(*itEffector);
            }
			
            RemoveFromWorldSystem();
		}
	}
}