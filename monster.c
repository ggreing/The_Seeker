#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "interface.h"
#include "monster.h"
#include "stage.h"
#include "Player.h"
#include "Sound.h"

MOB m[100];
node_t* OPEN = NULL, * CLOSED = NULL;
node_stack_t* STACK = NULL;
int t_posX = 0;
int t_posY = 0;
int countMob = 0;
int isMoving;
void init_astar() {

	node_t* temp;
	node_stack_t* stack;

	while (OPEN) {
		temp = OPEN->next_node;
		free(OPEN);
		OPEN = temp;
	}

	while (CLOSED) {
		temp = CLOSED->next_node;
		free(CLOSED);
		CLOSED = temp;
	}

	while (STACK) {
		stack = STACK->next_node;
		free(STACK);
		STACK = stack;
	}

}
int is_available_grid(int x, int y) {

	if (STAGE[y][x] == 1) {
		return 0;
	}

	return 1;

}
node_t* is_open(int x, int y) {

	node_t* temp = OPEN;

	while (temp) {
		if (temp->x == x && temp->y == y)
			return temp;
		temp = temp->next_node;
	}

	return NULL;
}
node_t* is_closed(int x, int y) {

	node_t* temp = CLOSED;

	while (temp) {
		if (temp->x == x && temp->y == y)
			return temp;
		temp = temp->next_node;
	}

	return NULL;

}
void push_into_stack(node_t* node) {

	node_stack_t* temp;

	temp = (node_stack_t*)calloc(1, sizeof(node_stack_t));
	temp->node = node;
	temp->next_node = STACK;
	STACK = temp;

}
node_t* pop_from_stack() {

	node_t* temp;
	node_stack_t* stack;

	stack = STACK;
	temp = stack->node;
	STACK = stack->next_node;

	free(stack);

	return temp;

}
void make_sort(node_t* old) {

	node_t* direct, * previousNode;
	int i;
	int degree = old->degree + 1;

	for (i = 0; i < 8; i++) {

		if ((direct = old->direct[i]) == NULL)
			continue;

		if (direct->degree > degree) {
			direct->prev_node = old;
			direct->degree = degree;
			direct->value_factor = direct->distance + direct->degree;
			push_into_stack(direct);
		}

	}

	while (STACK) {

		previousNode = pop_from_stack();

		for (i = 0; i < 8; i++) {

			if ((direct = previousNode->direct[i]) == NULL)
				break;

			if (direct->degree > previousNode->degree + 1) {
				direct->prev_node = previousNode;
				direct->degree = previousNode->degree + 1;
				direct->value_factor = direct->distance + direct->degree;
				push_into_stack(direct);
			}
		}
	}
}
void insert_node(node_t* present) {

	node_t* old = NULL, * temp = NULL;

	if (OPEN == NULL) {
		OPEN = present;
		return;
	}

	temp = OPEN;

	//OPEN�� �ִ� ��尡 ���� �ڽ� ��庸�� ��ġ�� ������
	//OPEN��带 �����ؼ� ���� �ڽ� ��庸�� ��ġ�� ���� ��带 ã�´�. 
	while (temp && (temp->value_factor < present->value_factor)) {
		old = temp;
		temp = temp->next_node;
	}

	//���� ��ġ�� OpenNode �� ������� ���� ����� ��� -> �߰��� �ڽ� ��� -> ���� ��ġ�� OpenNode�� ������� ���� �� ���
	if (old) {
		present->next_node = temp;
		old->next_node = present;
	}
	else {
		present->next_node = temp;
		OPEN = present;
	}

}
void extend_child_node(node_t* node, int x, int y, int dest_x, int dest_y, int cur_direct) {

	node_t* old = NULL, * child = NULL;
	int degree = node->degree + 1;

	if (old = is_open(x, y)) {

		node->direct[cur_direct] = old;

		//�׸��� ��� �翬�� �� ���� . ����� ��� ������ �ݴ�� ����ȴٴ� �� ����� ��. 
		if (degree < old->degree) {
			old->prev_node = node;
			old->degree = degree;
			old->value_factor = old->distance + old->degree;
		}//if()

	}
	else if (old = is_closed(x, y)) {

		node->direct[cur_direct] = old;

		//� ��쿡�� ���� CloseNode�� �ִ� ����� degree�� �� ���� ��찡 �߻��� ���� �ִµ�
		//�� �� ������ �ٽ� ����      
		if (degree < old->degree) {
			old->prev_node = node;
			old->degree = degree;
			old->value_factor = old->distance + old->degree;
			make_sort(old);
		}//if()

	//Ȯ���� ��� ���� �� OpenNode ����Ʈ�� �߰�
	}
	else {
		if ((child = (node_t*)calloc(1, sizeof(node_t))) == NULL)
			return;

		child->prev_node = node;
		child->degree = degree;
		child->distance = (x - dest_x) * (x - dest_x) + (y - dest_y) * (y - dest_y);
		child->value_factor = child->distance + child->degree;
		child->x = x;
		child->y = y;

		insert_node(child);

		node->direct[cur_direct] = child;

	}

}
char make_child(node_t* node, int dest_x, int dest_y) {

	int x, y;
	char flag = 0;
	char checkis_available_grid[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	x = node->x;
	y = node->y;

	//�̵� �������� ���� �Ǵ�.
	checkis_available_grid[DIRECTION_RIGHTDOWN] = is_available_grid(x, y + 1);
	checkis_available_grid[DIRECTION_DOWN] = is_available_grid(x, y + 1);
	checkis_available_grid[DIRECTION_LEFTDOWN] = is_available_grid(x - 1, y + 1);
	checkis_available_grid[DIRECTION_LEFT] = is_available_grid(x - 1, y);
	checkis_available_grid[DIRECTION_LEFTUP] = is_available_grid(x - 1, y - 1);
	checkis_available_grid[DIRECTION_UP] = is_available_grid(x, y - 1);
	checkis_available_grid[DIRECTION_RIGHTUP] = is_available_grid(x + 1, y - 1);
	checkis_available_grid[DIRECTION_RIGHT] = is_available_grid(x + 1, y);

	//�� �̵� ������ ��忡 ���� �ڽ� ��� ���� 
	if (checkis_available_grid[DIRECTION_LEFT]) {
		extend_child_node(node, x - 1, y, dest_x, dest_y, 3);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_RIGHT]) {
		extend_child_node(node, x + 1, y, dest_x, dest_y, 4);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x, y - 1, dest_x, dest_y, 1);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x, y + 1, dest_x, dest_y, 6);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_RIGHTDOWN] && checkis_available_grid[DIRECTION_RIGHT] && checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x + 1, y + 1, dest_x, dest_y, 7);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_LEFTUP] && checkis_available_grid[DIRECTION_LEFT] && checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x - 1, y - 1, dest_x, dest_y, 0);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_RIGHTUP] && checkis_available_grid[DIRECTION_RIGHT] && checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x + 1, y - 1, dest_x, dest_y, 2);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_LEFTDOWN] && checkis_available_grid[DIRECTION_LEFT] && checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x - 1, y + 1, dest_x, dest_y, 5);
		flag = 1;
	}//if()

	return flag;

}//char MakeChild(node_t* node, int dest_x, int dest_y)
node_t* find_path(int start_x, int start_y, int dest_x, int dest_y) {

	node_t* present, * best = NULL;
	int count = 0;

	//���� ��ġ ��� �߰� 
	present = (node_t*)calloc(1, sizeof(node_t));
	present->degree = 0;
	present->distance = (dest_x - start_x) * (dest_x - start_x) + (dest_y - start_y) * (dest_y - start_y);
	present->value_factor = present->distance;
	present->x = dest_x;
	present->y = dest_y;

	OPEN = present;

	while (1) {

		if (OPEN == NULL)
			return best;

		best = OPEN;					   //�� �������� ���鼭 OpenNode�� �ĺ��κ��� Ž���� �켱 �õ��մϴ�. 
		OPEN = best->next_node;     //�׸��� �� ���� ��尡 OpenNode�� �ֻ��� �ĺ����� �����Ǹ� 
		best->next_node = CLOSED;  //���ݱ��� ����� ������ ��带 �̹��� Ž���� best���� ���������ν� 
												//������� Ž����  ������ ���� �����ϰ� �˴ϴ�. 
		CLOSED = best;						//�� best���� �̹� �������� Ž�� �õ��ǹǷ� close���� ���� �Ǵ°���. 


		if (best == NULL)
			return NULL;

		//������ ����.
		if (best->x == start_x && best->y == start_y)
			return best;

		if (make_child(best, start_x, start_y) == 0 && count == 0)
			return NULL;

		count++;

	}

	return best;

}
node_t* b;
void gotoxy(int x, int y)
{
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}
void deleteMob(int sx, int sy) {
	gotoxy(sx * 2, sy);
	printf("  ");
	STAGE[sy][sx] = 0;
}
void showMob(int nx, int ny) {
	gotoxy(nx * 2, ny);
	STAGE[ny][nx] = 5;
	printf("��");
}
void monsterMove(int i, int tx, int ty, int d) {
	int nx, ny;
	int flag = 0;
	b = (node_t*)malloc(sizeof(node_t));
	init_astar();
	b = find_path(m[i].mobx, m[i].moby, tx, ty);
	b = b->next_node;
	nx = b->x;
	ny = b->y;
	if ((nx >= m[i].mobx - 1 && nx <= m[i].mobx + 1) && (ny >= m[i].moby - 1 && ny <= m[i].moby + 1)) {
		deleteMob(m[i].mobx, m[i].moby);
		showMob(nx, ny);
		m[i].mobx = nx;
		m[i].moby = ny;
	}
	if (nx == player.playerPos.X / 2 && ny == player.playerPos.Y) {
		Sound_Play(DAMAGE);
		player.life--;
		m[i].mobHasTarget = 0;
		return;
	}
	if (nx == tx && ny == ty) {
		m[i].mobHasTarget = 0;
	}
}

void isMonsterInRange(int d, COORD t_pos) {
	for (int i = 0; i < countMob; i++) {
		if (m[i].mobx == player.playerPos.X / 2 && m[i].moby == player.playerPos.Y) {
			if (d % 30 == 0) {
				Sound_Play(DAMAGE);
				player.life--;
				m[i].mobHasTarget = 0;
			}
			return;
		}
	}
	for (int i = 0; i < countMob; i++) {
		if (STAGE[m[i].moby][m[i].mobx] == EMPTY_SPACE) {
			m[i].mobx = -1;
			m[i].moby = -1;
		}
	}

	for (int i = 0; i < countMob; i++) {
		if ((m[i].mobx >= t_pos.X / 2 - 5 && m[i].mobx <= t_pos.X / 2 + 5) && (m[i].moby >= t_pos.Y - 5 && m[i].moby <= t_pos.Y + 5) && m[i].mobx != t_pos.X / 2 && m[i].moby != t_pos.Y) {
			t_posX = t_pos.X / 2;
			t_posY = t_pos.Y;
			m[i].mobHasTarget = 1;
		}
	}
	for (int i = 0; i < countMob; i++) {
		if (m[i].mobHasTarget) {
			if (d % 10 == 0) {
				monsterMove(i, t_posX, t_posY, d);
			}
		}
	}
}
void MonsterInit() {
	for (int i = 0; i < countMob; i++) {
		m[i].mobx = -1;
		m[i].moby = -1;
		m[i].mobHasTarget = 0;
	}
	countMob = 0;
	for (int i = 0; i < STAGE_Y; i++) {
		for (int j = 0; j < STAGE_X / 2; j++) {
			if (STAGE[i][j] == MONSTER) {
				m[countMob].mobx = j;
				m[countMob].moby = i;
				m[countMob].mobHasTarget = 0;
				countMob++;
			}
		}
	}
}