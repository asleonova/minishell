#include "minishell.h"

void append_lst(t_list **lst, void *new_content) 
{ 
    /* 1. allocate node */
    t_list *new_node;
	t_list *last;
	
	new_node = malloc(sizeof(t_list)); 
	last = *lst;  /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->content  = new_content; 
  
    /* 3. This new node is going to be the last node, so make next of 
          it as NULL*/
    new_node->next = NULL; 
  
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*lst == NULL) 
    { 
       *lst = new_node; 
       return; 
    } 
  
    /* 5. Else traverse till the last node */
    while (last->next != NULL) 
        last = last->next; 
  
    /* 6. Change the next of last node */
    last->next = new_node; 
    return; 
}