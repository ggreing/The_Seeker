#pragma once
#include<stdio.h>
#include<Windows.h>

//노드에 대한 정의
typedef struct node_s {
	int degree;                          //현재 이 노드의 깊이 값. 즉, 자료 구조 트리에서 깊이 값. 
	int distance;                        //이 노드로부터 목적지까지의 거리
	int value_factor;                   //평가치 값( degree + distance ) 

	int x, y;                           //이 노드의 위치 (그리드의 위치) 
	struct node_s* direct[8];       //확장 가능한 8방향에 대한 노드
	struct node_s* prev_node;    //링크드 리스트 이전 노드 
	struct node_s* next_node;     //링크드 리스트 다음 노드 

} node_t;

//노드를 재정렬할 때 쓸 스택.
typedef struct node_stack_s {
	node_t* node;                            //이 스택 위치에서 가리키고 있는 노드 
	struct node_stack_s* next_node;    //이 스택의 다음 위치  
} node_stack_t;

typedef struct mob {
	int mobx;
	int moby;
	int mobHasTarget;
}MOB;

extern int countMob;
enum {
	DIRECTION_LEFT, DIRECTION_LEFTUP, DIRECTION_UP, DIRECTION_RIGHTUP, DIRECTION_RIGHT,
	DIRECTION_RIGHTDOWN, DIRECTION_DOWN, DIRECTION_LEFTDOWN
};

void init_astar();
int is_available_grid(int x, int y);
node_t* is_open(int x, int y);
node_t* is_closed(int x, int y);
void push_into_stack(node_t* node);
node_t* pop_from_stack();
void make_sort(node_t* old);
void insert_node(node_t* present);
void extend_child_node(node_t* node, int x, int y, int dest_x, int dest_y, int cur_direct);
char make_child(node_t* node, int dest_x, int dest_y);
node_t* find_path(int start_x, int start_y, int dest_x, int dest_y);
void monsterMove(int i, int tx, int ty, int d);
void isMonsterInRange(int d, COORD t_pos);
COORD t_pos;
void MonsterInit();
