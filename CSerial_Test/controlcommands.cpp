#include "controlcommands.h"
#include "serial.h"
controlCommands::controlCommands()
{

}

void controlCommands::printChars(char *str){
    int clientNo;
    int choice;
    bool validity;
        if ((str[0] & 0xFF) == 0x00){
            cout<<"Master command"<<endl;
        } else{
            clientCommand(str,clientNo,choice,validity);
            cout<<"Client NO. "<<clientNo<<" voted for: "<<(char)((int)'A'+choice)<<endl;
        }


}

int controlCommands::checkValidity(char *str, int len){
    int isValid = 1;
    for (int p = 0; p<len; ++p)
        {
            if((str[p] & 0xFF)==0x00) break;
            if((str[p] & 0xFF)!=(start_response[p] & 0xFF)) {isValid = 0;  }
            //printf("0x%02x ? 0x%02x ", (str[p] & 0xFF),start_response[p] & 0xFF);
        }
        //printf("\n");

        return isValid;
}

int controlCommands::masterCommand(char *str){

    return 0;

}

void controlCommands::clientCommand(char *str, int &clientNo, int &choice, bool &validity){

   clientNo= (str[1] & 0x0F) + (16*(str[0] & 0xFF));
   choice  = str [4] & 0x0F;
   validity = true;

}
