#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100000
#define MAXCHAR 200
int i=0;
struct node
{
    char data[MAXCHAR];
    struct node* left;
    struct node* right;
};
struct node* newNode(char *value)
{
    struct node* new_node=malloc(sizeof(struct node));
    strcpy(new_node->data,value);
    new_node->left=NULL;
    new_node->right=NULL;

    return new_node;
};
struct node* insert(struct node* node, char *word) {
     if (node == NULL)
        return newNode(word);
     if (strcasecmp(word,node->data)<0)
        node->left  = insert(node->left, word);
     else if (strcasecmp(word,node->data)>0)
        node->right = insert(node->right, word);
     return node;
     }

struct node *parse_words(char *filename)
{
    struct node *root = NULL;
    char str[MAXCHAR];
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
        {
        printf("Could not open file %s",filename);
        }
    fgets(str,MAXCHAR,fp);
    str[strlen(str)-1]='\0';
    root = insert(root,str);
    while (fgets(str, MAXCHAR, fp)!= NULL)
    {
            str[strlen(str)-1]='\0';
            root = insert(root, str);
            i++;
    }

    fclose(fp);


    return root;
}
int height(struct node* root)
{
    if (root==NULL)
       return 0;
   else
   {
       /* compute the depth of each subtree */
       int left_height = height(root->left);
       int right_height = height(root->right);

       /* use the larger one */
       if (left_height > right_height)
           return(left_height+1);
       else return(right_height+1);
   }
}

struct node* search(struct node *r, char *val)
{
    struct node* temp;
    temp=r;
    while (temp!=NULL)
        {
            if (strcasecmp(val,temp->data)==0)
            return temp;
    else if (strcasecmp(val,temp->data)<0)
        temp =temp->left;
        else
            temp = temp->right;

        }
        return NULL;
}

struct node* get_leaf_node(struct node* root,char *key)
{
    while(root!=NULL)
    {
        if(strcasecmp(key,root->data)<0)
        {
            if(root->left==NULL)
                return root;
            else
                root=root->left;
        }
        else if(strcasecmp(key,root->data)>0)
        {
            if(root->right==NULL)
                return root;
            else
                root=root->right;
        }
    }
};
char predecessor[MAXCHAR];
char successor[MAXCHAR];
 void successorPredecessor(struct node *root, char val[]) {
		if (root != NULL) {
			if (strcasecmp(root->data,val)==0) {
				// go to the right most element in the left subtree, it will the predecessor
				if (root->left != NULL) {
					struct node *t = root->left;
					while (t->right != NULL) {
						t = t->right;
					}
					strcpy(predecessor,t->data);
				}
				if (root->right != NULL) {
					// go to the left most element in the right subtree, it will the successor
					struct node *t = root->right;
					while (t->left != NULL) {
						t = t->left;
					}
					strcpy(successor,t->data);
				}
			} else if (strcasecmp(val,root->data)<0) {

					strcpy(successor,root->data);
				successorPredecessor(root->left, val);
			} else if (root->data < val) {

					strcpy(predecessor,root->data);
				successorPredecessor(root->right, val);
			}
		}
	}


int main()
{
    //some variables for splitting the paragraph
    struct node* temporary;
    //
    int max_height;
    char statement[MAXCHAR];
    struct node* root1;
    char *filename="EN-US-Dictionary.txt";
    root1 = parse_words(filename);
    //print the size
    printf("The size of the tree is = %d\n",i+1);
    //print the height
    max_height=height(root1);
    printf("The height of the tree = : %d\n",max_height-1);
    //searching
    printf("Enter word to search for:\n");
    gets(statement);
    char *token =strtok(statement," ");
    while(token!=NULL)
    {
        temporary=search(root1,token);
        if(temporary!=NULL)
        {
            printf("%s",temporary->data);
            printf(" - CORRECT \n");
        }
        else
        {
            printf("\n%s - ",token);
            printf("Incorrect, Suggestions : ");
           struct node* t;
           t=get_leaf_node(root1,token);
           printf("%s ",t->data);
           successorPredecessor(root1,t->data);
           printf("%s ",successor);
           printf("%s ",predecessor);
           printf("\n\n");

        }
        token=strtok(NULL," ");
    }


    return 0;
}
