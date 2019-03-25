ss ss1 { 

	state initEVR{ // set up the EVR and wait for the event clock PLL to lock
		entry{
			//set up EVR
		}
		
		when(//PLL_LOCk){
			//do something
		}state initSync
	
	}

	state initSync{ //Load the sync sequence, connect to event 125 (run once)
		entry{
			//load sequence
		}
		
		when(//checkSync-CMD){
			//do something
		}state checkSync
	
	
	}

	state checkSync{ //load the check sync sequence and connect to event 125 (run forever). Eventually we can resync if we loose lock
		entry{
			//load sequence
		}
		
		when(//reSync-CMD){
			//do somthing
		}state initSync
	}
}