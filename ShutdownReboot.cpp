#include <iostream>
#include <wiringPi.h>

#include <unistd.h> // usleep

using namespace std;

int main(){
	cout << "Shutdown-Reboot gestartet" << endl;
	
	// wiringpi Init
	wiringPiSetup();
	
	#define REBOOT_PIN 9
	#define SHUTDOWN_PIN 7
	
	pinMode ( SHUTDOWN_PIN, INPUT);
	pinMode ( REBOOT_PIN, INPUT);
	
	pullUpDnControl( SHUTDOWN_PIN, PUD_UP );
	pullUpDnControl( REBOOT_PIN, PUD_UP );
	
	bool shutdown_pressed = false;
	bool reboot_pressed   = false;
	
	while(true){
		
		if( digitalRead (SHUTDOWN_PIN) == LOW ){
			if( shutdown_pressed == true)
				continue;
			shutdown_pressed = true;
			cout << "sudo shutdown -h now" << endl;
			system("sudo shutdown -h now");
		}else
			shutdown_pressed = false;
		
		if( digitalRead (REBOOT_PIN) == LOW ){
			if( reboot_pressed == true)
				continue;
			reboot_pressed = true;
			cout << "sudo reboot" << endl;
			system("sudo reboot");
		}else
			reboot_pressed = false;
		
		usleep(10000);
	}
}
