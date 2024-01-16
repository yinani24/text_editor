#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <stack>
using namespace std;

void write_to_file(std::string writing_file, std::vector<std::string> reading_file){
    std::ofstream F;
    F.open(writing_file);
    if(F){
        for(unsigned i = 0; i < reading_file.size(); i++)
            F<<reading_file[i]<<'\n';
    }
    F.close();
} 

void insertion(std::vector<std::string> * file, std::string string, int scroll_side, int scroll_up, int start){
    unsigned replace_till = 20 - scroll_side;
    int movement = start + scroll_up;
    int count = 0;
    int size = static_cast<int>((*file).size()) - 1;
    unsigned temp;
    
    do{
        if(movement > size && movement <= 29)
            (*file).resize((movement + 1));
            
        if(movement <= 29)
            (*file).at(movement).resize(20,' ');
        else
            break;
        
        if(string.length() <= replace_till && count == 0){
            (*file).at(movement).replace(scroll_side,string.length(),string);
            replace_till = 0;
        }
        else{
            temp = replace_till;
            
            if(replace_till < string.length())
                replace_till = string.length() - temp;
            else
                replace_till = temp;
            
            if(count == 0){
                (*file).at(movement).replace(scroll_side,temp,string,0,temp);
                string = string.substr(temp,replace_till);
                movement++;
                count = 1;
            }
            else if(movement <= 29 && count != 0){
                
                if(replace_till > 20){
                    (*file).at(movement).replace(0,20,string,0,20);
                    replace_till = replace_till - 20;
                    string = string.substr(20,replace_till);
                }
                else{
                    (*file).at(movement).replace(0,string.length(),string,0,string.length());
                    replace_till = 0;
                }
                
                movement++;
            }
            else   
                break;
        }
    }while(replace_till != 0);

}


int input_taker(std::string input, std::vector<std::string> file){
    std::string storage;
    //std::vector<std::string> sep;
    std::stringstream X(input);
    std::getline(X,storage,' ');
    
    if(storage == "save"){
        std::getline(X,storage,' ');
        write_to_file(storage,file);
    }
    else if(storage == "d" || storage == "s"){
        std::getline(X, storage, ' ');
        if(storage == "d" || storage == "s")
            return 1;
        else
            return stoi(storage);
    }
    else if(storage == "a" || storage == "w"){
        std::getline(X, storage, ' ');    
        if(storage == "a" || storage == "w")
            return -1;
        else
            return (-1 * stoi(storage));
    }
    
    return 0;
}

void display(std::vector<std::string> file, int * counter1, int * counter2, int * start, std::string input){
    int side_move = 7 + *counter1;
    int i;
    //counter1 = for column movement
    //counter2 = for row movement
    if (side_move > 26){
        std::cout<<std::setw(26)<<"*\n";
        (*counter1) = 19;
    }
    else if(side_move < 7){
        std::cout<<std::setw(7)<<"*\n";
        (*counter1) = 0;
    }
    else
        std::cout<<std::setw(side_move)<<"*\n";
    
    std::cout<<"     "<<"12345678901234567890\n";
    int mover;
    int count = 0;
    int store = 0;
    std::string storage;
    std::stringstream X(input);
    std::getline(X,storage,' ');
    if(storage == "s"){
        std::getline(X, storage, ' ');
        if(storage == "s")
            store = 1;
        else
            store = stoi(storage);
    }
    else if(storage == "w"){
        std::getline(X, storage, ' ');    
        if(storage == "w")
            store = -1;
        else
            store = (-1 * stoi(storage));
    }
    
    int size = static_cast<int>(file.size());
    int sizeoflines = size - 1;

    (*counter2) += store;

    if(store < 0 && (*counter2) < 0){
       (*start) += store;
        if((*start) >= 0){
            int random = -1 * store;
            (*counter2) += random;
        }
    }

    if((*counter2) > 9){
        (*counter2) = 9;
        if(store > 0)
            (*start) += store;
        count = 1;
    }

    /*if((*counter2) > (sizeoflines - (*start))){    
        int difference = (*counter2) - sizeoflines + (*start);
        if(count == 0){    
            (*counter2) = (*counter2) - store - difference;
            (*start) += difference;
        }
        else{
            (*counter2) = (*counter2) - difference;
        }
    }*/

    if((*counter2) > (sizeoflines - (*start))){    
        int difference = (*counter2) - sizeoflines + (*start);
        if(count == 0){    
            (*start) += difference;
            (*counter2) = sizeoflines - (*start);
        }
        else{
            (*counter2) = (*counter2) - difference;
        }
    }

    if((*counter2) < 0){
        (*counter2) = 0;
        //(*start) += store;
    }
    
    if((*start) > sizeoflines)
        (*start) = sizeoflines;
    else if((*start) < 0)
        (*start) = 0;

    int up_cursor = int (*counter2);
    
    //std::cout<< "Counter 2 " << (*counter2) <<'\n';
    //std::cout<< "Start " << (*start) <<'\n';
    
    // we need 2 variables 11 
    //two situations if cursor reach bottom of the screen and bottom of the file
    //dont move the cursor at the end
    //cursor to be moved up and starting line to be moved down
    //keep the cursor between 0 - 9 if the cursor is at 9 it is at bottom line
    //cursor == file lines - start lines - 1 
    //v_cursor = [0,9]
    //v_cursor == 9, start++
    //v_cursor == total - start - 1 -> v_cursor--, start++
    // to move up do start-- 
    //help provided by the ta
    //made a lot of changes to fit my code

    i = (*start);
    
    int ending = i + 9;

    for(; i <= ending; i++){
            mover = 4;
            if(i < size){
                if(i == ((*start) + up_cursor)){
                    mover = 3;
                    std::cout<<"*";
                }
                std::cout<<std::setw(mover)<<(i+1)<<"|"<<file.at(i)<<'\n';
            }
            else
                std::cout<<std::setw(mover)<<(i+1)<<'\n';        
    }


    /*if(counter_fake < 10){
        for(i = 0; i < 10; i++){
            mover = 4;
            if(i < file.size()){
                if(i == counter_fake){
                    mover = 3;
                    std::cout<<"*";
                }
                std::cout<<std::setw(mover)<<(i+1)<<"|"<<file.at(i)<<'\n';
            }
            else
                std::cout<<std::setw(mover)<<(i+1)<<'\n';        
        }
    }

    else{    
        for(i = (counter_fake - 9); i <= counter_fake; i++){
            mover = 4;
            if(i < file.size()){
                if(i == counter_fake || i == (file.size() - 1)){
                    mover = 3;
                    std::cout<<"*";
                }
                std::cout<<std::setw(mover)<<(i+1)<<"|"<<file.at(i)<<'\n';
            }
            else
                std::cout<<std::setw(mover)<<(i+1)<<'\n';        
        }
    }*/
    //(*count_for_loop) = counter_fake;

    std::cout<<"     "<<"12345678901234567890\n";
}

int whereMagicHappens(char s[]){
    std::fstream F;
    std::vector<std::string> file_line;
    std::string input;
    unsigned lines = 0;
    unsigned i = 0;
    std::string x;
    int counter1 = 0;
    int counter2 = 0; 
    int start = 0;
    int count_for_undo = 0;
    int count_for_redo = 0;
    int number_of_insertions = 0;
    //int count_for_unsaved = 0;
    stack<vector<string>> undo_stack;
    stack<vector<string>> redo_stack;
    string inputting_yes_no;
    //*counter1 = 0;  // for inc and dec of a and d
    //*counter2 = 0; //for inc and dec of w and s
    std::string storage_string;
    std::string previous_command_string;
    F.open(s);
    
    if(!F){
        std::cout<<"Failed to open file: "<< s <<'\n';
        return 2;
    }
    
    while(std::getline(F,input)){
        file_line.push_back(input); 
        lines++;
    }
    
    F.close();
    
    if(lines > 30){
        std::cout<<"File " << s <<" has too many lines.\n";
        return 2;  
    }   
        //lines = 0;   
    for(i = 0; i < file_line.size(); i++){
        if(file_line[i].length() > 20){
            std::cout<<"File " << s <<" has at least one too long line.\n";
            return 2;
        } 
    }
    
    undo_stack.push(file_line);
    
    do{
        display(file_line, &counter1, &counter2, &start, x);
        std::cout<<"Enter command: ";
        std::getline(std::cin,x);
        
        if(x == "q" && number_of_insertions == 0){
            std::cout<<"\nGoodbye!\n";
            break;
        }
        else if(x == "q" && number_of_insertions != 0){
            cout<<"You have unsaved changes.\nAre you sure you want to quit (y or n)?\n";
            getline(cin,inputting_yes_no);
            if(inputting_yes_no == "y"){
                std::cout<<"\nGoodbye!\n";
                break;
            }else if(inputting_yes_no == "n")
                continue;
        }
        
        if(x.empty()){
            if(previous_command_string.empty()){
                std::cout<<"\nNo previous command.\n\n";
                continue;
            }
            else    
                x = previous_command_string;
        }
        
        std::cout<<'\n';
        previous_command_string = x;
        std::stringstream SS(x);
        getline(SS, storage_string, ' ');
        
        if(storage_string == "a" || storage_string == "d")
            counter1 += input_taker(x, file_line);
        //else if(storage_string == "w" || storage_string == "s"){
        //    counter2 += input_taker(x, file_line);
            //if(counter2 >= 9)
            //    start += input_taker(x, file_line);
        //}
        else if(storage_string == "i"){
            std::getline(SS, storage_string);
            insertion(&file_line, storage_string,counter1,counter2, start);
            undo_stack.push(file_line);
            count_for_undo++;
            number_of_insertions++;
            //count_for_unsaved++;
            
            if(count_for_redo > 0){
                count_for_redo = 0;
                while(!redo_stack.empty())
                    redo_stack.pop();
            }    
        
        }
        else if(storage_string == "u"){
            
            if(count_for_undo == 0){
                cout<<"Cannot undo.\n\n";
                number_of_insertions = 0;
            }   
            else{
                vector<string> undo_operation;
                undo_operation = undo_stack.top();
                redo_stack.push(undo_operation);
                undo_stack.pop();
                file_line = undo_stack.top();
                count_for_undo--;
                count_for_redo++;
                number_of_insertions++;
            }
        
        }
        else if(storage_string == "r"){
            
            if(count_for_redo == 0){
                cout<<"Cannot redo.\n\n";
                //number_of_insertions = 0;
            }
            else{
                file_line = redo_stack.top();
                undo_stack.push(file_line);
                redo_stack.pop();
                count_for_redo--;
                count_for_undo++;
                number_of_insertions--;
            }
        
        }
        else if(storage_string == "save"){
            number_of_insertions = 0;
            //count_for_unsaved = 0;
            input_taker(x, file_line);
        }

    }while(1);
    
    return 0;
}

int main(int argc, char * argv[]){
    int return_value;
    
    if(argc < 2){
        std::cout<<"Too few command-line arguments.\n";
        return 1;
    }
    else if(argc > 2){
        std::cout<<"Too many command-line arguments.\n";
        return 1;
    }
    else{
        return_value = whereMagicHappens(argv[1]);               
    }
    
    return return_value;
}