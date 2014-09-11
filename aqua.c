#include <stdlib.h>
#include <aqua.h>
#include <list.h>
#include <crecre.h>

aqua* init_aqua(){
	
	aqua *aq = (aqua*)malloc(sizeof(aqua));

	aq->twb_tank = init_list();
	aq->f1_tank = init_list();
	aq->trash_tank = init_list();
	
	return aq;
}

void delete_aqua(aqua *_aqua){
	delete_list(_aqua->twb_tank);
	delete_list(_aqua->f1_tank);
	delete_list(_aqua->trash_tank);
	free(_aqua);
}

void process_repro(aqua *_aqua){
	process_list(_aqua->twb_tank, repro);
	process_list(_aqua->f1_tank, repro);
	process_list(_aqua->trash_tank, repro);
}

void process_reap(aqua *_aqua){
	process_list(_aqua->twb_tank, reap);
	process_list(_aqua->f1_tank, reap);
	process_list(_aqua->trash_tank, reap);
}

void process_selection(aqua *_aqua){
	selection(_aqua, _aqua->twb_tank);
	selection(_aqua, _aqua->f1_tank);
	selection(_aqua, _aqua->trash_tank);
}

void selection(aqua *_aqua, list *_ll){

	node *n;
	crecre *cre;
	char gen;

	for(n = _ll->head; n; n = n->next){

		cre = (crecre*)n->data;
		gen = get_genome(cre->lgens, 'T');

		if(gen == 'B' && _ll == _aqua->twb_tank && cre->age > 100){
			
			unlink_node(_ll, n);
			add_list(_aqua->f1_tank, cre, delete_crecre, print_crecre);
		}

		if(gen == 'T' && _ll != _aqua->twb_tank && cre->age > 100){
			unlink_node(_ll, n);
			add_list(_aqua->twb_tank, cre, delete_crecre, print_crecre);
		}
	}
}