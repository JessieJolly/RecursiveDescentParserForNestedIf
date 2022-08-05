//This is the recursive descent parser for the statement:
//if ( c ) { if ( c ) {...if ( c ) { stmt ; } else { stmt ; }...} else { stmt ; } } else { stmt; }

//The corresponding grammar is:
//S' --> S | S'S
//S --> B | B else { S } | A
//B --> if ( c ) { S }
//A --> stmt;

//Enter $ to indicate end of input

#include<stdio.h>
#include<string.h>

char* S(char *_token, const char s[2]);
char* _S(char *_token, const char s[2]);

//function to move pointer
char* moveip(char *_token, const char s[2]){ 
    if(_token != "$"){
        return strtok(NULL, s);
    }
    else{
        return NULL;
    }
}

//function for symbol A
//A --> stmt ;
char* A(char *_token, const char s[2]){
    int value;
    if(_token != NULL && strcmp(_token, "stmt")==0){
        _token = moveip(_token,s);
        if(_token != NULL && strcmp(_token, ";")==0){
            _token = moveip(_token,s);
            return _token;
        }
        else{
            return NULL;
        }
    }
    else{
        return NULL;
    }
}

//function for symbol B
//B --> if ( c ) { S }
char* B(char *_token, const char s[2]){ 
    int value;
    if(_token != NULL && strcmp(_token, "if") == 0){
        _token = moveip(_token, s);
        if(_token != NULL && strcmp(_token, "(") == 0){
            _token = moveip(_token, s);
            if(_token != NULL && strcmp(_token, "c") == 0){
                _token = moveip(_token, s);
                if(_token != NULL && strcmp(_token, ")") == 0){
                    _token = moveip(_token, s);
                    if(_token != NULL && strcmp(_token, "{") == 0){
                        _token = moveip(_token, s);
                        _token = S(_token, s);
                        if(_token != NULL && strcmp(_token,"}") == 0){
                            _token = moveip(_token, s);
                            return _token;
                        }
                        else{
                            return NULL;
                        }
                    }
                    else{
                        return NULL;
                    }
                }
                else{
                    return NULL;
                }
            }
            else{
                return NULL;
            }
        }
        else{
            return NULL;
        }
    }
    else{
        return NULL;
    }
}

//function for start symbol S
//S --> B | B else { S } | A
char* S(char *_token, const char s[2]){ 
    if(strcmp(_token, "$")==0){
        return _token;
    }
    char* temptok;
    temptok = B(_token, s); 
    if(temptok != NULL){
        if(strcmp(temptok, "else")==0){
            temptok = moveip(temptok, s);
            if(temptok != NULL && strcmp(temptok, "{")==0){
                temptok = moveip(temptok, s);
                temptok = S(temptok, s);
                if(temptok != NULL && strcmp(temptok, "}")==0){
                    temptok = moveip(temptok, s); 
                    _token = temptok;
                    return _token; 
                }
                else{
                    return NULL;
                }
            }
            else{
                return NULL;
            }
        }
        else{
            _token = temptok;
            return _token;
        }
    } 
    temptok = A(_token, s);
    if(temptok != NULL){ 
        if(strcmp(temptok, "}")==0 || strcmp(temptok, "$")==0){
            _token = temptok;
            return _token;
        }   
        return _token;
    }
}

//function for starting symbol S'
//S' --> S | SS'
char* _S(char *_token, const char s[2]){
    if(strcmp(_token, "$")==0){
        return _token;
    }
    char* temptok;
    temptok = S(_token, s);
    if(temptok != NULL){
        if(strcmp(temptok, "$")==0){
            return temptok;
        }
        temptok = _S(temptok, s);
    }
}


//main function
void main(){
    char command[100];
    int invalid = 0;
    printf("Enter command:\n");
    scanf("%[^\n]", command);   
    const char s[2] = " ";
    char *token;
   
    /* get the first token */
    token = strtok(command, s); 
    //call the function defined for start symbol
    char* final = _S(token, s);  
    if(final != NULL && strcmp(final, "$")==0){
        printf("Valid command\n");
    }
    else{
        printf("Invalid command\n");
    } 

}