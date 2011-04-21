using UnityEngine;
using System.Collections;

public class WwiseEngineManager : MonoBehaviour
{
	private static bool isInstanceCreated = false; //singleton check.
	
	
	#region Public Members

    /// <summary>
    /// these sound bank are loaded while the sound engine creation and unload when the sound engine is destroyed.
    /// For specific "level" sound bank, use LoadBank and UnloadBank methods...
    /// </summary>
	public string[] OverallBankNames;
    public string BasePath = "TODO";
    public string LangSpecificDirName = "English(US)/";

    #endregion
	
	void Awake()
	{
		if (isInstanceCreated)
		{
			Debug.LogError("[WwiseEngineManager] don't create 2 WwiseEngineManager. Because WwiseEngine implementation is based on a singleton, it's useless to have 2 manager instance.");
			Debug.Break();
		}
		isInstanceCreated = true;
		
		WwiseEngine.Initialize(BasePath, LangSpecificDirName);
		
		WwiseEngine.LoadSoundBanks(OverallBankNames);
		
		WwiseEngine.Update();
	}
	
	void Update()
	{
		WwiseEngine.Update();
	}
	
	void OnDisable()
	{
		WwiseEngine.Dispose();
	}
}
