#include "pins.h"

int period = 1000;

bool game_over = false;

int pos1 = 3;
int pos2 = 6;
int posbx = 4;
int posby = 3;
int y_ball_direction = 1;
int x_ball_direction = 1;

int last_button_1 = digitalRead(button1);
int last_button_2 = digitalRead(button2);
int last_button_3 = digitalRead(button3);
int last_button_4 = digitalRead(button4);

int c = 0;


void setup(){
    int i = 0 ;
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    pinMode(button3, INPUT);
    pinMode(button4, INPUT);
    for(i=2;i<18;i++)
    {
        pinMode(i, OUTPUT);
    }
    for(i=2;i<18;i++) {
        digitalWrite(i, LOW);
    }
    digitalWrite(row5, LOW);
    digitalWrite(row6, LOW);
    digitalWrite(row7, LOW);
    digitalWrite(row8, LOW);
}

void loop(){
    c++;
    if((c/period) * period == c){
        move_ball();
    }
    if(button_right_1()){
        go_right(1);
    }
    if(button_left_1()){
        go_left(1);
    }
    if(button_right_2()){
        go_right(2);
    }
    if(button_left_2()){
        go_left(2);
    }
    if(game_over){
        clear_matrix();
    }
    else{
        display_ball();
        display_player1();
        display_player2();
    }
}


void move_ball(){
    int new_posy = posby + y_ball_direction;
    if(new_posy == 0){
        if(player2_has_ball()){
            period = period - 50;
            y_ball_direction = -1 * y_ball_direction;
            posby = posby + y_ball_direction;
        }
        else{
            game_over = true;
        }
    }
    else if(new_posy == 7){
        if(player1_has_ball()){
            period = period - 50;
            y_ball_direction = -1 * y_ball_direction;
            posby = posby + y_ball_direction;
        }
        else{
            game_over = true;
        }
    }
    else{
        posby = new_posy;

    }

    if(posbx == 0 || posbx == 7){
        x_ball_direction = -1 * x_ball_direction;
        posbx = posbx + x_ball_direction;
    }
    else{
        posbx = posbx + x_ball_direction;

    }
}

bool player1_has_ball(){
    switch(posbx){
        case 0:
            return (pos1 ==1);
        case 1:
            return (pos1 == 1 || pos1 == 2);
        case 2:
            return (pos1 == 1 || pos1 == 2 || pos1 == 3);
        case 3:
            return (pos1 == 2 || pos1 == 3 || pos1 == 4);
        case 4:
            return (pos1 == 3 || pos1 == 4 || pos1 == 5);
        case 5:
            return (pos1 == 4 || pos1 == 5 || pos1 == 6);
        case 6:
            return (pos1 == 5 || pos1 == 6);
        case 7:
            return (pos1 == 6);
    }
}

bool player2_has_ball(){
    switch(posbx){
        case 0:
            return (pos2 ==1);
        case 1:
            return (pos2 == 1 || pos2 == 2);
        case 2:
            return (pos2 == 1 || pos2 == 2 || pos2 == 3);
        case 3:
            return (pos2 == 2 || pos2 == 3 || pos2 == 4);
        case 4:
            return (pos2 == 3 || pos2 == 4 || pos2 == 5);
        case 5:
            return (pos2 == 4 || pos2 == 5 || pos2 == 6);
        case 6:
            return (pos2 == 5 || pos2 == 6);
        case 7:
            return (pos2 == 6);
    }
}

void display_ball(){
    clear_matrix();
    switch(posby){
        case 0:
            digitalWrite(row1, HIGH);
            break;
        case 1:
            digitalWrite(row2, HIGH);
            break;
        case 2:
            digitalWrite(row3, HIGH);
            break;
        case 3:
            digitalWrite(row4, HIGH);
            break;
        case 4:
            digitalWrite(row5, HIGH);
            break;
        case 5:
            digitalWrite(row6, HIGH);
            break;
        case 6:
            digitalWrite(row7, HIGH);
            break;
        case 7:
            digitalWrite(row8, HIGH);
            break;
    }
    switch(posbx){
        case 0:
            digitalWrite(col1, LOW);
            break;
        case 1:
            digitalWrite(col2, LOW);
            break;
        case 2:
            digitalWrite(col3, LOW);
            break;
        case 3:
            digitalWrite(col4, LOW);
            break;
        case 4:
            digitalWrite(col5, LOW);
            break;
        case 5:
            digitalWrite(col6, LOW);
            break;
        case 6:
            digitalWrite(col7, LOW);
            break;
        case 7:
            digitalWrite(col8, LOW);
            break;
    }
}

bool button_right_1(){
    int button_state = digitalRead(button1);
    if(button_state != last_button_1){
        last_button_1 = button_state;
        return button_state == LOW;
    }
    return false;
}

bool button_left_1(){
    int button_state = digitalRead(button2);
    if(button_state != last_button_2){
        last_button_2 = button_state;
        return button_state == LOW;
    }
    return false;
}

bool button_right_2(){
    int button_state = digitalRead(button4);
    if(button_state != last_button_4){
        last_button_4 = button_state;
        return button_state == LOW;
    }
    return false;
}

bool button_left_2(){
    int button_state = digitalRead(button3);
    if(button_state != last_button_3){
        last_button_3 = button_state;
        return button_state == LOW;
    }
    return false;
}


void clear_matrix(){
    digitalWrite(row1, LOW);
    digitalWrite(row2, LOW);
    digitalWrite(row3, LOW);
    digitalWrite(row4, LOW);
    digitalWrite(row5, LOW);
    digitalWrite(row6, LOW);
    digitalWrite(row7, LOW);
    digitalWrite(row8, LOW);
    digitalWrite(col1, HIGH);
    digitalWrite(col2, HIGH);
    digitalWrite(col3, HIGH);
    digitalWrite(col4, HIGH);
    digitalWrite(col5, HIGH);
    digitalWrite(col6, HIGH);
    digitalWrite(col7, HIGH);
    digitalWrite(col8, HIGH);
}


void go_right(int player){
    switch(player){
        case 1:
            if(pos1 < 6){
                pos1 = pos1 + 1;
            }
            break;
        case 2:
            if(pos2 < 6){
                pos2 = pos2 + 1;
            }
            break;
    }
}


void go_left(int player){
    switch(player){
        case 1:
            if(pos1 > 1){
                pos1 = pos1 - 1;
            }
            break;
        case 2:
            if(pos2 > 1){
                pos2 = pos2 - 1;
            }
            break;
    }
}


void display_player2() {
    clear_matrix();
    digitalWrite(row1, HIGH);
    switch(pos2){
        case 1:
            digitalWrite(col1, LOW);
            digitalWrite(col2, LOW);
            digitalWrite(col3, LOW);
            break;
        case 2:
            digitalWrite(col2, LOW);
            digitalWrite(col3, LOW);
            digitalWrite(col4, LOW);
            break;
        case 3:
            digitalWrite(col3, LOW);
            digitalWrite(col4, LOW);
            digitalWrite(col5, LOW);
            break;
        case 4:
            digitalWrite(col4, LOW);
            digitalWrite(col5, LOW);
            digitalWrite(col6, LOW);
            break;
        case 5:
            digitalWrite(col5, LOW);
            digitalWrite(col6, LOW);
            digitalWrite(col7, LOW);
            break;
        case 6:
            digitalWrite(col6, LOW);
            digitalWrite(col7, LOW);
            digitalWrite(col8, LOW);
            break;
    }
}

void display_player1() {
    clear_matrix();
    digitalWrite(row8, HIGH);
    switch(pos1){
        case 1:
            digitalWrite(col1, LOW);
            digitalWrite(col2, LOW);
            digitalWrite(col3, LOW);
            break;
        case 2:
            digitalWrite(col2, LOW);
            digitalWrite(col3, LOW);
            digitalWrite(col4, LOW);
            break;
        case 3:
            digitalWrite(col3, LOW);
            digitalWrite(col4, LOW);
            digitalWrite(col5, LOW);
            break;
        case 4:
            digitalWrite(col4, LOW);
            digitalWrite(col5, LOW);
            digitalWrite(col6, LOW);
            break;
        case 5:
            digitalWrite(col5, LOW);
            digitalWrite(col6, LOW);
            digitalWrite(col7, LOW);
            break;
        case 6:
            digitalWrite(col6, LOW);
            digitalWrite(col7, LOW);
            digitalWrite(col8, LOW);
            break;
    }
}
