using UnityEngine;
using System.Collections;

[AddComponentMenu("Wwise/WwiseListener")]
public class WwiseListener: MonoBehaviour
{
    #region Public Members

    /// <summary>
    /// Define the listener index of this listener.
    /// Range between 0 to 7
    /// </summary>
    public int ListenerIndex = 0;

    #endregion

    #region MonoBehaviour Override

	void Start ()
	{
		if (ListenerIndex > 7 || ListenerIndex < 0)
		{
			Debug.LogError("WwiseListener : the listener index is out of range [0..7] : " + ListenerIndex);
			Debug.Break();
		}

		// init the listener based on the sound Engine
		// nothing to do... just update its position.
	}
	
	// Update is called once per frame
	void Update () 
    {
		WwiseEngine.SetSoundListenerPosition(ListenerIndex, transform.position, transform.forward, transform.up);
    }

    #endregion
}
