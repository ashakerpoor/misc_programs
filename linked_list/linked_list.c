#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STR_MAX 100
#define STR_MIN 20


// Structure that defines a dictionary element that
// holds the original word's length and the first 4 letters.
struct dic_pair {
	int wlen;
	char word[5];
};
typedef struct dic_pair pair_t;


// Structure that defines a dictionary type of node.
struct dic {
	pair_t element;
	struct dic *next;
};
typedef struct dic dic_t;


// This is a helper function. It constructs a node,
// and returns a pointer to the node.
dic_t *create_node (char *str) {
        size_t slen = strlen(str);
        dic_t *node = malloc(sizeof(dic_t));
        node->element.wlen = strlen(str);

	// if a word has 4 or more characters,
	// then copy up to the first 4 chars.
        if (slen >= 4) {
                strncpy(node->element.word, str, 4);
                node->element.word[4] = '\0';
        }
	// if a word has less than 4 characters,
	// then copy all the chars.
        else {
                strncpy(node->element.word, str, slen);
                node->element.word[slen] = '\0';
        };
        node->next = NULL;

        return node;
};


// Parse a string and store the words in a linked list.
dic_t *parse_n_store(char *str) {
        int i = 0;
        char buffer[STR_MIN] = {};
        dic_t *head, *current;
        head = NULL;

        while(*str) {
		// if the char is a space, we have a full word stored into "buffer".
                if(*str == ' ') {
                        current = create_node(buffer);
                        current->next = head; // head is pointing to the prev item at this point.
                        head = current; // here we set the head to point to the current item.
                        memset(buffer, '\0', sizeof buffer);
                        i = 0;
                }
		// else, continue concatenating chars.
                else {
                        buffer[i] = *str;
                        i++;
                }
                str++;
        }
        current = create_node(buffer);
        current->next = head;
        head = current;
        return head;
};


// This function takes in a pointer to the head of
// a current linked list and sorts it alphabetically.
void sortll(dic_t **head) {
	dic_t **prev, *curr, *nxt;
	int done, i;
	done = 0;

	// exit the function if the list is empty or has one member.
	if (*head == NULL || (*head)->next == NULL) return;

	while (!done) {
		prev = head;	// pointer to the node before the current node.
		curr = *head;	// pointer to the current node.
		nxt = (*head)->next;  // pointer to the next node.
		done = 1;

		while (nxt) {
        	    i = strcasecmp(curr->element.word, nxt->element.word);

	            if (i>0) {
        	        curr->next = nxt->next;
                	nxt->next = curr;
	                *prev = nxt;
        	        done = 0;
	            }
        	    prev = &curr->next;
	            curr = nxt;
        	    nxt = nxt->next;
	        }
	}
}


// It takes in the head pointer to a current list,
// along with a string to compare against each node.
// The search mode could be case sensitive (smode==1),
// or case insensitive (smode == 0).
// The function reeturns a pointer to a matched up entry,
// or NULL, otherwise.
dic_t *search (dic_t *head, char *str, int smode) {
        int i;
        char str_[5] = {};
        dic_t *p, *empty, var;

        var.element.wlen = 0;
        strncpy(var.element.word, "null", 4);
        var.element.word[4] = '\0';
        empty = &var;

        p = head;
        strncpy(str_, str, 4);
        str_[strlen(str_)] = '\0';

        // if the search mode is case sensitive.
        if (smode) {
                while (p != NULL) {
                        i = strcmp(p->element.word, str_);
                        if (i==0) return p;
                        p = p->next;
                }
                return empty;
        }
        // if the search mode is case insensitive.
        else{
                while (p != NULL) {
                        i = strcasecmp(p->element.word, str_);
                        if (i==0) return p;
                        p = p->next;
                }
                return empty;
        }
}


// It adds entries to the current linked list alphabetically.
dic_t *insert_node (dic_t *head, char *str) {
        int i;
        char str_[5] = {};
        dic_t *p, *q;

        p = head;
        strncpy(str_, str, 4);
        str_[strlen(str_)] = '\0';
        i = strcasecmp(str_, p->element.word);

        // handle the case when a node is added to the head of the list.
        if (i<0) {
		q = create_node (str);
                q->next = p;
                p = q;
                return q;
        }
        // handle other cases where a node is inserted in the body or added to the tail.
        else {
                while(i>0) {
                        if (p->next == NULL) {
				q = create_node (str);
                                p->next = q;
                                return head;
                        }
                        i = strcasecmp(str_, p->next->element.word);
                        if (i<0) continue;
                        p = p->next;
                }
		q = create_node (str);
                q->next = p->next;
                p->next = q;
                return head;
        }
}


// It deletes a current linked list at &head.
void deletell (dic_t **head) {  // we pass a pointer to pointer so we can modify the pointer itself.
        dic_t *p, *q;
        p = *head;
        while (p != NULL) {
                q = p->next;
                p = NULL;
                p = q;
        }
        *head = NULL;
}


// This function prints out a linked list.
void printll (dic_t *head) {
        dic_t *temp = head;
        while (temp != NULL) {
                printf("%s:%d-> ", temp->element.word, temp->element.wlen);
                temp = temp->next;
        }
        printf("\n");
}



int main()
{
// "str" stores a longer string (i.e. a sentence).
// "short_str" can store shorter strings (i.e. words).
char str[STR_MAX] = {}, short_str[STR_MIN] = {};
dic_t *p1, *p2;

printf("Input your sentence:\n");
scanf("%[^\n]s", str);
p1 = parse_n_store(str);

// Uncomment this block if you want to print the list.
/*
printll(p1);
*/

// Uncomment this block if you want to sort and print the list.
/*
sortll(&p1);
printll(p1);
*/

// Uncomment this block if you want to add a node.
/*
printf("Input a word:\n");
scanf("%s", short_str);
p2 = insert_node (p1, short_str);
printll(p2);
*/

// Uncomment this block if you want to delete the list.
/*
deletell(&p2);
printll(p2);
*/

// Uncomment this block if you want to prompt a search.
// Note that the function returns "null" if it does not find a match.
/*
printf("Input a word:\n");
scanf("%s", short_str);
p2 = search(p1, short_str, 1);
printf("%s %d\n", p2->element.word, p2->element.wlen);
*/

return 0;
}
