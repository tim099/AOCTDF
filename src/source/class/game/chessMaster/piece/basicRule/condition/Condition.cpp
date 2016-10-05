#include "class/game/chessMaster/piece/basicRule/condition/Condition.h"
#include <cstdio>
namespace CM {

Condition::Condition() {
	ui=0;
	do_and=true;
}
Condition::~Condition() {

}
void Condition::save(FILE* file){
	fprintf(file,"do and=%d\n",do_and);
	save_condition(file);
}
void Condition::load(FILE* file){
	int ope;
	fscanf(file,"do and=%d\n",&ope);
	if(ope){
		do_and=true;
	}else{
		do_and=false;
	}
	load_condition(file);
}
} /* namespace CM */
