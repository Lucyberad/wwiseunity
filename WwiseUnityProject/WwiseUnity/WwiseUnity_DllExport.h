#ifndef WWISEUNITY_WWISEUNITY_DLLEXPORT_H
#define WWISEUNITY_WWISEUNITY_DLLEXPORT_H

#define EXPORT_DLL __declspec(dllexport)

// just include header as last as possible to avoid compatibility issue
#include "WwiseEngine.hpp"
#include "WwiseUnityTypes.hpp"

// Engine configuration
extern "C"
{
	EXPORT_DLL void DestroyEngine()
	{
		WwiseUnity::WwiseEngine::killSingleton();
	}

	EXPORT_DLL bool Init()
	{
		return WwiseUnity::WwiseEngine::getInstance()->Init();
	}

	EXPORT_DLL void ProcessAudio()
	{
		WwiseUnity::WwiseEngine::getInstance()->ProcessAudio();
	}

	EXPORT_DLL void Term()
	{
		WwiseUnity::WwiseEngine::getInstance()->Term();
	}

	EXPORT_DLL int SetBasePath(WU_STRING basePath)
	{
		return WwiseUnity::WwiseEngine::getInstance()->SetBasePath(basePath);
	}
	EXPORT_DLL int SetLangSpecificDirName(WU_STRING specificDirName)
	{
		return WwiseUnity::WwiseEngine::getInstance()->SetLangSpecificDirName(specificDirName);
	}

	EXPORT_DLL int LoadBank(WU_STRING bankName)
	{
		return WwiseUnity::WwiseEngine::getInstance()->LoadBank(bankName);
	}

	EXPORT_DLL int UnloadBank(WU_STRING bankName)
	{
		return WwiseUnity::WwiseEngine::getInstance()->UnloadBank(bankName);
	}

	EXPORT_DLL void SetState(WU_STRING stateGroup, WU_STRING state)
	{
		WwiseUnity::WwiseEngine::getInstance()->SetState(stateGroup, state);
	}
	EXPORT_DLL void SetStateById(unsigned long stateGroupId, unsigned long stateId)
	{
		WwiseUnity::WwiseEngine::getInstance()->SetState(stateGroupId, stateId);
	}

	// Game Object management
	EXPORT_DLL int RegisterGameObject(unsigned int akId, WU_STRING gameObjectLabel)
	{
		return WwiseUnity::WwiseEngine::getInstance()->RegisterGameObject(akId, gameObjectLabel);
	}

	EXPORT_DLL int UnregisterGameObject(unsigned int akId)
	{
		return WwiseUnity::WwiseEngine::getInstance()->UnregisterGameObject(akId);
	}
	EXPORT_DLL int UnregisterAllGameObject()
	{
		return WwiseUnity::WwiseEngine::getInstance()->UnregisterAllGameObject();
	}

	EXPORT_DLL int SetPosition(unsigned int gameObjectId, float posX, float posY, float posZ, float orientationX, float orientationY, float orientationZ)
	{
		AkSoundPosition soundPosition;
		soundPosition.Position.X = posX;
		soundPosition.Position.Y = posY;
		soundPosition.Position.Z = posZ;

		soundPosition.Orientation.X = orientationX;
		soundPosition.Orientation.Y = orientationY;
		soundPosition.Orientation.Z = orientationZ;

		return WwiseUnity::WwiseEngine::getInstance()->SetPosition(gameObjectId, soundPosition);
	}
	EXPORT_DLL int SetPositionByListener(unsigned int gameObjectId, float posX, float posY, float posZ, float orientationX, float orientationY, float orientationZ, int listenerIndex)
	{
		AkSoundPosition soundPosition;
		soundPosition.Position.X = posX;
		soundPosition.Position.Y = posY;
		soundPosition.Position.Z = posZ;

		soundPosition.Orientation.X = orientationX;
		soundPosition.Orientation.Y = orientationY;
		soundPosition.Orientation.Z = orientationZ;

		return WwiseUnity::WwiseEngine::getInstance()->SetPosition(gameObjectId, soundPosition, listenerIndex);
	}

	EXPORT_DLL void PostEvent(WU_STRING eventName, unsigned int gameObject)
	{
		WwiseUnity::WwiseEngine::getInstance()->PostEvent(eventName, gameObject);
	}
	EXPORT_DLL void PostEventById(unsigned long eventId, unsigned int gameObject)
	{
		WwiseUnity::WwiseEngine::getInstance()->PostEvent(eventId, gameObject);
	}

	EXPORT_DLL void SetRTPCValueGlobal(WU_STRING rtpcName, float value)
	{
		WwiseUnity::WwiseEngine::getInstance()->SetRTPCValue(rtpcName, value);
	}
	EXPORT_DLL void SetRTPCValue(WU_STRING rtpcName, float value, unsigned int  gameObjectId)
	{
		WwiseUnity::WwiseEngine::getInstance()->SetRTPCValue(rtpcName, value, gameObjectId);
	}
	EXPORT_DLL void SetRTPCValueById(unsigned long rtpcId, float value, unsigned int  gameObjectId)
	{
		WwiseUnity::WwiseEngine::getInstance()->SetRTPCValue(rtpcId, value, gameObjectId);
	}

	EXPORT_DLL void SetSwitch(WU_STRING switchGroupName, WU_STRING switchName, unsigned int gameObjectId)
	{
		WwiseUnity::WwiseEngine::getInstance()->SetSwitch(switchGroupName, switchName, gameObjectId);
	}
	EXPORT_DLL void SetSwitchById(unsigned long switchGroupId, unsigned long switchId, unsigned int gameObjectId)
	{
		WwiseUnity::WwiseEngine::getInstance()->SetSwitch(switchGroupId, switchId, gameObjectId);
	}

	// Listener Management
	EXPORT_DLL int SetListenerPosition(float posX, float posY, float posZ, float orientationFrontX, float orientationFrontY, float orientationFrontZ, float orientationTopX, float orientationTopY, float orientationTopZ)
	{
		AkListenerPosition akPosition;
		akPosition.Position.X = posX;
		akPosition.Position.Y = posY;
		akPosition.Position.Z = posZ;

		akPosition.OrientationFront.X = orientationFrontX;
		akPosition.OrientationFront.Y = orientationFrontY;
		akPosition.OrientationFront.Z = orientationFrontZ;
		
		akPosition.OrientationTop.X = orientationTopX;
		akPosition.OrientationTop.Y = orientationTopY;
		akPosition.OrientationTop.Z = orientationTopZ;

		return WwiseUnity::WwiseEngine::getInstance()->SetListenerPosition(akPosition);
	}
	EXPORT_DLL int SetListenerPositionById(int listenerIndex, float posX, float posY, float posZ, float orientationFrontX, float orientationFrontY, float orientationFrontZ, float orientationTopX, float orientationTopY, float orientationTopZ)
	{
		AkListenerPosition akPosition;
		akPosition.Position.X = posX;
		akPosition.Position.Y = posY;
		akPosition.Position.Z = posZ;

		akPosition.OrientationFront.X = orientationFrontX;
		akPosition.OrientationFront.Y = orientationFrontY;
		akPosition.OrientationFront.Z = orientationFrontZ;
		
		akPosition.OrientationTop.X = orientationTopX;
		akPosition.OrientationTop.Y = orientationTopY;
		akPosition.OrientationTop.Z = orientationTopZ;

		return WwiseUnity::WwiseEngine::getInstance()->SetListenerPosition(listenerIndex, akPosition);
	}

	EXPORT_DLL int SetGameObjectActiveListeners(unsigned int gameObjectId, unsigned int listenerMask)
	{
		return WwiseUnity::WwiseEngine::getInstance()->SetGameObjectActiveListeners(gameObjectId, listenerMask);
	}
}

#endif