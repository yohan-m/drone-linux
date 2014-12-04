#include "control.h"

void initControl()
{


}


void sendNavDataInit(int seqNum)
{
	int seqSize = 0;
    char seqStr[64];
    numberToString(seqNum,seqStr,&seqSize);
    
    char * cfg = (char *)malloc((41+seqSize)*sizeof(char));
    memcpy(cfg,"AT*CONFIG=",10);
    memcpy(&cfg[10],seqStr,seqSize);
    memcpy(&cfg[10+seqSize],",\"general:navdata_demo\",\"TRUE\"\r",31);

    writeCmd(cfg,41+seqSize);
    
    free(cfg);
}


void sendResetWatchdog(int seqNum)
{
    int seqSize = 0;
    char seqStr[64];
    numberToString(seqNum,seqStr,&seqSize);

    char * rstw = (char *)malloc((11+seqSize)*sizeof(char));

    memcpy(rstw,"AT*COMWDG=",10);
    memcpy(&rstw[10],seqStr,seqSize);
    memcpy(&rstw[10+seqSize],"\r",1);

    writeCmd(rstw,11+seqSize);

    free(rstw);
}


void sendEmergency(int seqNum)
{
    int seqSize = 0;
    char seqStr[64];
    numberToString(seqNum,seqStr,&seqSize);

    char * reset = (char *)malloc((18+seqSize)*sizeof(char));

    memcpy(reset,"AT*REF=",7);
    memcpy(&reset[7],seqStr,seqSize);
    memcpy(&reset[7+seqSize],",290717952\r",11);

    writeCmd(reset,18+seqSize);

    free(reset);
}


void sendCalibHPlan(int seqNum)
{
    int seqSize = 0;
    char seqStr[64];
    numberToString(seqNum,seqStr,&seqSize);

    char * calib = (char *)malloc((10+seqSize)*sizeof(char));

    memcpy(calib,"AT*FTRIM=",9);
    memcpy(&calib[9],seqStr,seqSize);
    memcpy(&calib[9+seqSize],"\r",1);
    
    writeCmd(calib,10+seqSize);

    free(calib);
}


void sendCalibMagn(int seqNum)
{
    int seqSize = 0;
    char seqStr[64];
    numberToString(seqNum,seqStr,&seqSize);

    char * calib = (char *)malloc((12+seqSize)*sizeof(char));

    memcpy(calib,"AT*CALIB=",9);
    memcpy(&calib[9],seqStr,seqSize);
    memcpy(&calib[9+seqSize],",0\r",3);

    writeCmd(calib,12+seqSize);

    free(calib);
}


void sendTakeOff(int seqNum)
{
    int seqSize = 0;
    char seqStr[64];
    numberToString(seqNum,seqStr,&seqSize);

    char * takeoff = (char *)malloc((18+seqSize)*sizeof(char));

    memcpy(takeoff,"AT*REF=",7);
    memcpy(&takeoff[7],seqStr,seqSize);
    memcpy(&takeoff[7+seqSize],",290718208\r",11);

    writeCmd(takeoff,18+seqSize);

    free(takeoff);
}


void sendLand(int seqNum)
{
    int seqSize = 0;
    char seqStr[64];
    numberToString(seqNum,seqStr,&seqSize);

    char * land = (char *)malloc((18+seqSize)*sizeof(char));

    memcpy(land,"AT*REF=",7);
    memcpy(&land[7],seqStr,seqSize);
    memcpy(&land[7+seqSize],",290717696\r",11);

    writeCmd(land,18+seqSize);

    free(land);
}


void sendMovement(int seqNum, int flag, float leftRightTilt, float frontBackTilt, float verticalSpeed, float angularSpeed)
{
    int seqSize = 0;
    char seqStr[64];
    numberToString(seqNum,seqStr,&seqSize);
        
    int cflagSize = 0;
    char cflagStr[64];
    numberToString(flag,cflagStr,&cflagSize);

    int lrTilt_int = *(int*)&leftRightTilt;
    int fbTilt_int = *(int*)&frontBackTilt;
    int vSpeed_int = *(int*)&verticalSpeed;
    int aSpeed_int = *(int*)&angularSpeed;
    
    int lrTiltSize = 0;
    char lrTiltStr[64];
    numberToString(lrTilt_int,lrTiltStr,&lrTiltSize);
        
    int fbTiltSize = 0;
    char fbTiltStr[64];
    numberToString(fbTilt_int,fbTiltStr,&fbTiltSize);
    
    int vSpeedSize = 0;
    char vSpeedStr[64];
    numberToString(vSpeed_int,vSpeedStr,&vSpeedSize);
    
    int aSpeedSize = 0;
    char aSpeedStr[64];
    numberToString(aSpeed_int,aSpeedStr,&aSpeedSize);

    char * move = (char *)malloc((14+seqSize+cflagSize+lrTiltSize+fbTiltSize+vSpeedSize+aSpeedSize)*sizeof(char));

    memcpy(move,"AT*PCMD=",8);
    memcpy(&move[8],seqStr,seqSize);
    memcpy(&move[8+seqSize],",",1);
    memcpy(&move[9+seqSize],cflagStr,cflagSize);
    memcpy(&move[9+seqSize+cflagSize],",",1);
    memcpy(&move[10+seqSize+cflagSize],lrTiltStr,lrTiltSize);
    memcpy(&move[10+seqSize+cflagSize+lrTiltSize],",",1);
    memcpy(&move[11+seqSize+cflagSize+lrTiltSize],fbTiltStr,fbTiltSize);
    memcpy(&move[11+seqSize+cflagSize+lrTiltSize+fbTiltSize],",",1);
    memcpy(&move[12+seqSize+cflagSize+lrTiltSize+fbTiltSize],vSpeedStr,vSpeedSize);
    memcpy(&move[12+seqSize+cflagSize+lrTiltSize+fbTiltSize+vSpeedSize],",",1);
    memcpy(&move[13+seqSize+cflagSize+lrTiltSize+fbTiltSize+vSpeedSize],aSpeedStr,aSpeedSize);
    memcpy(&move[13+seqSize+cflagSize+lrTiltSize+fbTiltSize+vSpeedSize+aSpeedSize],"\r",1);

    writeCmd(move,14+seqSize+cflagSize+lrTiltSize+fbTiltSize+vSpeedSize+aSpeedSize);

    free(move);
}


void numberToString(int number, char * str, int * size)
{
	*size = sprintf(str, "%d", number);
}


void writeCmd(char * data, int size) 
{
	//printf("%.*s\n", size, data);
}
