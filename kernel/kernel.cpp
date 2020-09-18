#include "kernel.h"


void kernel_main() {
    screen::clear_screen();
    screen::kprint((char *)"Test!\n");
    //char chr[1024] = "";
    //for(int i = 0; i < 1024; i++){
    //    chr[i] = 0x72-32;
    //}
    //screen::kprint(chr);
    screen::kprint((char *)"Lets Test Malloc With a psuedo random number generator.\n");
    
    int i = 5;
    int n,n2;
    char * buffer;
    rand::srand(1880);
    buffer = (char*) mem::malloc (i+1);
    if (buffer==NULL){
        screen::kprint((char *)"That should not have happened!\n");
    } else {
    for (n=0; n<i; n++)
      buffer[n]=rand::rand()%26+'a';
    buffer[i]='\0';
    screen::kprint((char *)"Random String:");
    screen::kprint(buffer);
    screen::kprint((char *)"\n");
    
    

    mem::free (buffer);


    
    }
    screen::kprint((char *)"Lets Test vector with a psuedo random number generator.\n");
    vector<char *> v;
    rand::srand(200);
    for (n=0; n<5; n++){
      v.push_back((char *)(rand::rand()%26+'a'));
    }
    for(int i=0; i<v.size(); i++){
      screen::kprint(v[i]);
    }

    screen::kprint((char *)"\n");
    screen::kprint((char *)"Tests Complete!\n");
}

