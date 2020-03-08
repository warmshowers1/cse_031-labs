#include <stdio.h>

typedef struct node {
  int value;
  struct node *next;
} node;

int has_cycle(node *head)
{
	// Your code goes here:
	if(head == NULL){
		return 0;
	}

	struct node *p = head;
	struct node *q = p->next;
	while(NULL != p && NULL != q){
		if(p == q){
			return 1;
		}
		else if(q->next == p){
			return 1;
		}
		else if(NULL == q->next){
			return 0;
		}
		p = p->next;
		q = q->next->next;
	}
	return 0;
}

void test_has_cycle(void)
{
  int i;
  node nodes[25]; //enough to run our tests
  for(i=0; i < sizeof(nodes)/sizeof(node); i++) {
    nodes[i].next = NULL;
    nodes[i].value = i;
  }
  // No cycles here
  nodes[0].next = &nodes[1];
  nodes[1].next = &nodes[2];
  nodes[2].next = &nodes[3];
  printf("Checking first list for cycles. There should be none, has_cycle says it has %s cycle\n", has_cycle(&nodes[0])?"A":"NO");
  
  nodes[4].next = &nodes[5]; // Here <---------------.
  nodes[5].next = &nodes[6]; //			     |
  nodes[6].next = &nodes[7]; //			     |
  nodes[7].next = &nodes[8]; //			     |
  nodes[8].next = &nodes[9]; //			     |
  nodes[9].next = &nodes[10]; //		     |
  nodes[10].next = &nodes[4]; // Begins cycles here -*
  printf("Checking second list for cycles. There should be a cycle, has_cycle says it has %s cycle\n", has_cycle(&nodes[4])?"A":"NO");
  
  nodes[11].next = &nodes[12];
  nodes[12].next = &nodes[13];
  nodes[13].next = &nodes[14];
  nodes[14].next = &nodes[15]; // Here <-------------.
  nodes[15].next = &nodes[16]; //		     |
  nodes[16].next = &nodes[17]; //		     |
  nodes[17].next = &nodes[14]; // Begins cycle here -*
  printf("Checking third list for cycles. There should be a cycle, has_cycle says it has %s cycle\n", has_cycle(&nodes[11])?"A":"NO");
  
  nodes[18].next = &nodes[18]; // Points to itself
  printf("Checking fourth list for cycles. There should be a cycle, has_cycle says it has %s cycle\n", has_cycle(&nodes[18])?"A":"NO");
  
  // No cycles here
  nodes[19].next = &nodes[20];
  nodes[20].next = &nodes[21];
  nodes[21].next = &nodes[22];
  nodes[22].next = &nodes[23];
  printf("Checking fifth list for cycles. There should be none, has_cycle says it has %s cycle\n", has_cycle(&nodes[19])?"A":"NO");
  
  printf("Checking length-zero list for cycles. There should be none, has_cycle says it has %s cycle\n", has_cycle(NULL)?"A":"NO");
}

int main(void){
  test_has_cycle();
  return 0;
}
