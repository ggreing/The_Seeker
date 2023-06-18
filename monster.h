#pragma once
#include<stdio.h>
#include<Windows.h>

//��忡 ���� ����
typedef struct node_s {
	int degree;                          //���� �� ����� ���� ��. ��, �ڷ� ���� Ʈ������ ���� ��. 
	int distance;                        //�� ���κ��� ������������ �Ÿ�
	int value_factor;                   //��ġ ��( degree + distance ) 

	int x, y;                           //�� ����� ��ġ (�׸����� ��ġ) 
	struct node_s* direct[8];       //Ȯ�� ������ 8���⿡ ���� ���
	struct node_s* prev_node;    //��ũ�� ����Ʈ ���� ��� 
	struct node_s* next_node;     //��ũ�� ����Ʈ ���� ��� 

} node_t;

//��带 �������� �� �� ����.
typedef struct node_stack_s {
	node_t* node;                            //�� ���� ��ġ���� ����Ű�� �ִ� ��� 
	struct node_stack_s* next_node;    //�� ������ ���� ��ġ  
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
