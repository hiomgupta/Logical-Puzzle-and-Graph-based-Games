#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#define dim 2

enum {
    RED = 0,
    ORANGE = 5,
    BLUE = 1,
    GREEN = 4,
    WHITE = 2,
    YELLOW = 3
};

char color(int cc){
    switch (cc)
    {
    case RED:
        return 'R';
        break;
    case BLUE:
        return 'B';
        break;
    case ORANGE:
        return 'O';
        break;
    case GREEN:
        return 'G';
        break;
    case WHITE:
        return 'W';
        break;
    
    default:
        return 'Y';
        break;
    }
}


typedef char face[2][2];
typedef struct {
    face face0;
    face face1;
    face face2;
    face face3;
    face face4;
    face face5;
} cube_t;


void init_cube(cube_t* cube) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cube-> face0[i][j] = color(RED);
            cube-> face1[i][j] = color(BLUE);
            cube-> face2[i][j] = color(WHITE);
            cube-> face3[i][j] = color(YELLOW);
            cube-> face4[i][j] = color(GREEN);
            cube-> face5[i][j] = color(ORANGE);
        }
    }
}

void clockwise(face of,face cf){
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            switch (i+j)
            {
            case 0:
                of[i][j]= cf[1][0];
                break;
            case 1:
                if (i<j){
                of[i][j]= cf[0][0];
                break;
                }
                else{
                    of[i][j] = cf[1][1];
                    break;
                }   
            case 2:
                of[i][j]= cf[0][1];
                break;
            }
        }    
    }
    
}

void anticlockwise(face of,face cf){

    for (int i = 0; i < dim; i++)

    {
        for (int j = 0; j < dim; j++)
        {
            switch (i+j)
            {
            case 0:
                of[i][j]= cf[0][1];
                break;
            case 1:
                if (i<j){
                of[i][j]= cf[1][1];
                break;
                }
                else{
                    of[i][j] = cf[0][0];
                    break;
                }
                
            case 2:
                
                of[i][j]= cf[1][0];
                break;
            
            }
        }
        
    }
    
}

void printcube(cube_t* cube) {
    printf("Face 0 Front face: %c %c\n", cube->face0[0][0], cube->face0[0][1]);
    printf("                   %c %c\n", cube->face0[1][0], cube->face0[1][1]);
    printf("Face 1 Top face:   %c %c\n", cube->face1[0][0], cube->face1[0][1]);
    printf("                   %c %c\n", cube->face1[1][0], cube->face1[1][1]);
    printf("Face 2 Left face:  %c %c\n", cube->face2[0][0], cube->face2[0][1]);
    printf("                   %c %c\n", cube->face2[1][0], cube->face2[1][1]);
    printf("Face 3 Right face: %c %c\n", cube->face3[0][0], cube->face3[0][1]);
    printf("                   %c %c\n", cube->face3[1][0], cube->face3[1][1]);
    printf("Face 4 Bottom face:%c %c\n", cube->face4[0][0], cube->face4[0][1]);
    printf("                   %c %c\n", cube->face4[1][0], cube->face4[1][1]);
    printf("Face 5 Back Face:  %c %c\n", cube->face5[0][0], cube->face5[0][1]);
    printf("                   %c %c\n", cube->face5[1][0], cube->face5[1][1]);
}

void move_R(cube_t* cube) {
    // Save a temporary copy of the affected faces
    face temp_face0, temp_face1, temp_face2, temp_face3, temp_face4, temp_face5;

    // Copy the current state of the faces
    memcpy(temp_face0, cube->face0, sizeof(face));
    memcpy(temp_face1, cube->face1, sizeof(face));
    memcpy(temp_face2, cube->face2, sizeof(face));
    memcpy(temp_face3, cube->face3, sizeof(face));
    memcpy(temp_face4, cube->face4, sizeof(face));
    memcpy(temp_face5, cube->face5, sizeof(face));

    // Perform the R move (right face clockwise)
    for (int i = 0; i < dim; i++) {
        cube->face0[i][1] = temp_face4[i][1];
        cube->face1[i][1] = temp_face0[i][1];
        cube->face4[i][1] = temp_face5[i][0];
        cube->face5[i][0] = temp_face1[1-i][1];
    }
    clockwise(cube->face3,temp_face3);
}

void move_Rp(cube_t* cube) {
    // Save a temporary copy of the affected faces
    face temp_face0, temp_face1, temp_face2, temp_face3, temp_face4, temp_face5;

    // Copy the current state of the faces
    memcpy(temp_face0, cube->face0, sizeof(face));
    memcpy(temp_face1, cube->face1, sizeof(face));
    memcpy(temp_face2, cube->face2, sizeof(face));
    memcpy(temp_face3, cube->face3, sizeof(face));
    memcpy(temp_face4, cube->face4, sizeof(face));
    memcpy(temp_face5, cube->face5, sizeof(face));

    for (int i = 0; i < dim; i++) {
        cube->face0[i][1] = temp_face1[i][1];
        cube->face1[i][1] = temp_face5[1-i][0];
        cube->face4[i][1] = temp_face0[i][1];
        cube->face5[i][0] = temp_face4[1-i][1];
    }
    anticlockwise(cube->face3,temp_face3);
}


void move_U(cube_t* cube) {
    
    face temp_face0, temp_face1, temp_face2, temp_face3, temp_face4, temp_face5;

    
    memcpy(temp_face0, cube->face0, sizeof(face));
    memcpy(temp_face1, cube->face1, sizeof(face));
    memcpy(temp_face2, cube->face2, sizeof(face));
    memcpy(temp_face3, cube->face3, sizeof(face));
    memcpy(temp_face4, cube->face4, sizeof(face));
    memcpy(temp_face5, cube->face5, sizeof(face));

    
    for (int i = 0; i < dim; i++) {
        cube->face0[0][i] = temp_face3[0][i];
        cube->face2[0][i] = temp_face0[0][i];
        cube->face3[0][i] = temp_face5[0][i];
        cube->face5[0][i] = temp_face2[0][i];
    }
    clockwise(cube->face1,temp_face1);
}

void move_Up(cube_t* cube) {
    
    face temp_face0, temp_face1, temp_face2, temp_face3, temp_face4, temp_face5;

    
    memcpy(temp_face0, cube->face0, sizeof(face));
    memcpy(temp_face1, cube->face1, sizeof(face));
    memcpy(temp_face2, cube->face2, sizeof(face));
    memcpy(temp_face3, cube->face3, sizeof(face));
    memcpy(temp_face4, cube->face4, sizeof(face));
    memcpy(temp_face5, cube->face5, sizeof(face));

    anticlockwise(cube->face1,temp_face1);
    for (int i = 0; i < dim; i++) {
        cube->face0[0][i] = temp_face2[0][i];
        cube->face2[0][i] = temp_face5[0][i];
        cube->face3[0][i] = temp_face0[0][i];
        cube->face5[0][i] = temp_face3[0][i];
    }
    
}
void move_F(cube_t* cube) {
    
    face temp_face0, temp_face1, temp_face2, temp_face3, temp_face4, temp_face5;

    
    memcpy(temp_face0, cube->face0, sizeof(face));
    memcpy(temp_face1, cube->face1, sizeof(face));
    memcpy(temp_face2, cube->face2, sizeof(face));
    memcpy(temp_face3, cube->face3, sizeof(face));
    memcpy(temp_face4, cube->face4, sizeof(face));
    memcpy(temp_face5, cube->face5, sizeof(face));

    clockwise(cube->face0,temp_face0);
    for (int i = 0; i < dim; i++) {
        cube->face1[1][i] = temp_face2[1-i][1];
        cube->face2[i][1] = temp_face4[0][i];
        cube->face3[i][0] = temp_face1[1][i];
        cube->face4[0][i] = temp_face3[1-i][0];
    }
    
}
void move_Fp(cube_t* cube) {
    
    face temp_face0, temp_face1, temp_face2, temp_face3, temp_face4, temp_face5;

    
    memcpy(temp_face0, cube->face0, sizeof(face));
    memcpy(temp_face1, cube->face1, sizeof(face));
    memcpy(temp_face2, cube->face2, sizeof(face));
    memcpy(temp_face3, cube->face3, sizeof(face));
    memcpy(temp_face4, cube->face4, sizeof(face));
    memcpy(temp_face5, cube->face5, sizeof(face));

    anticlockwise(cube->face0,temp_face0);
    for (int i = 0; i < dim; i++) {
        cube->face1[1][i] = temp_face3[i][0];
        cube->face2[i][1] = temp_face1[1][1-i];
        cube->face3[i][0] = temp_face4[0][1-i];
        cube->face4[0][i] = temp_face2[i][1];
    }
    
}

void move_R2(cube_t* cube){
    move_R(cube);
    move_R(cube);
}
void move_U2(cube_t* cube){
    move_U(cube);
    move_U(cube);
}
void move_F2(cube_t* cube){
    move_F(cube);
    move_F(cube);
}

int complete(cube_t* cube){
    char x= cube->face0[0][0];
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (cube->face0[i][j] != x){
                return 0;
            }
        }
        
    }
    char y= cube->face1[0][0];
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (cube->face1[i][j] != y){
                return 0;
            }
        }
        
    }
    char z= cube->face2[0][0];
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (cube->face2[i][j] != z){
                return 0;
            }
        }
        
    }
    char a= cube->face3[0][0];
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (cube->face3[i][j] != a){
                return 0;
            }
        }
        
    }
    char b= cube->face4[0][0];
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (cube->face4[i][j] != b){
                return 0;
            }
        }
        
    }
    char c= cube->face5[0][0];
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (cube->face5[i][j] != c){
                return 0;
            }
        }
        
    }

    return 1;
     
}

typedef struct CubeState {
    cube_t cube;
    char moves[50]; // To store the sequence of moves to reach this state
} CubeState;

typedef struct QueueNode {
    CubeState state;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

void enqueue(Queue* queue, CubeState state) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->state = state;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

CubeState dequeue(Queue* queue) {
    if (queue->front == NULL) {
        CubeState emptyState;
        return emptyState;
    }
    CubeState state = queue->front->state;
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return state;
}

bool isSolved(cube_t* cube) {
    // Check if all faces are solved (all the same color)
    return complete(cube);
}

void solvePocketCube(cube_t* initialCube, int * count) {
    Queue queue;
    initQueue(&queue);
    int a =1;
    CubeState initialState;
    initialState.cube = *initialCube;
    memset(initialState.moves, 0, sizeof(initialState.moves));
    enqueue(&queue, initialState);
    
    while (queue.front) {
        CubeState currentState = dequeue(&queue);
        
        if (isSolved(&currentState.cube)) {
            
            printf("Solved! Sequence of moves: %s\n", currentState.moves);
            return;
        }
        CubeState childState = currentState;
        
        strcat(childState.moves, "R ");
        move_R(&childState.cube);
        enqueue(&queue, childState);
        
        
        CubeState childState1 = currentState;
        strcat(childState1.moves, "U ");
        move_U(&childState1.cube);
        enqueue(&queue, childState1);
        

        CubeState childState3 = currentState;
        strcat(childState3.moves, "F ");
        move_F(&childState3.cube);
        enqueue(&queue, childState3);

        CubeState childState4 = currentState;
        strcat(childState4.moves, "Rp ");
        move_Rp(&childState4.cube);
        enqueue(&queue, childState4);

        CubeState childState5 = currentState;
        strcat(childState5.moves, "Up ");
        move_Up(&childState5.cube);
        enqueue(&queue, childState5);

        CubeState childState6 = currentState;
        strcat(childState6.moves, "Fp ");
        move_Fp(&childState6.cube);
        enqueue(&queue, childState6);

        CubeState childState7 = currentState;
        strcat(childState7.moves, "R2 ");
        move_R2(&childState7.cube);
        enqueue(&queue, childState7);

        CubeState childState8 = currentState;
        strcat(childState8.moves, "U2 ");
        move_U2(&childState8.cube);
        enqueue(&queue, childState8);

        CubeState childState2 = currentState;
        strcat(childState2.moves, "F2 ");
        move_F2(&childState2.cube);
        enqueue(&queue, childState2);
        
        a+=9;

       
    }

    printf("Unable to solve the Pocket Cube.\n");
}

int main(int argc, char const *argv[]) {
    cube_t cube;
    int count= 0;
    init_cube(&cube);
    move_R(&cube);
    move_Fp(&cube);
    move_Up(&cube);

    

    printcube(&cube);

    // // Solve the Pocket Cube
    printf("Calculating moves....");
    solvePocketCube(&cube,&count);
    
    return 0;
}