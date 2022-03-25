#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char data[70];
    struct node *left,*right;
} node;
node* newnode(char* x)
{
    node* n = malloc(sizeof(node));
    strcpy(n->data,x);
    n->left = NULL;
    n->right = NULL;
    return n;
}
node* mainRoot= NULL;
node* insert(node* n,char* x)
{
    if(n==NULL)
    {
        n= newnode(x);
    }
    else if(strcasecmp(x,n->data)<0)
    {
        n->left = insert(n->left,x);
    }
    else
    {
        n->right = insert(n->right,x);
    }
    return n;
}
node* searchrecursive(node*n,char* x)
{
    if(n==NULL)
        return NULL;
    else if(strcasecmp(x,n->data)==0)
        return n;
    else if (strcasecmp(x,n->data)<0)
    {
        return searchrecursive(n->left,x);
    }
    else
    {
        return searchrecursive(n->right,x);
    }
}
node* nodeBeforeNull(node*n,char* x)
{
    node* temp=n;
    if(strcasecmp(x,n->data)==0)
        return n;
    else if (strcasecmp(x,n->data)<0)
    {
        temp=temp->left;
        if(temp==NULL)
            return n;
        else
            return nodeBeforeNull(n->left,x);
    }
    else
    {
        temp=temp->right;
        if(temp==NULL)
            return n;
        else
            return nodeBeforeNull(n->right,x);
    }
}

int count (node * root)
{
    if(root == NULL)
        return 0;
    else
        return 1+count(root->left)+count(root->right);
}
int Height( node* root)
{
    if (root == NULL)
        return -1;
    else
    {
        /* compute the depth of each subtree */
        int leftDepth = Height(root->left);
        int rightDepth = Height(root->right);

        /* use the larger one */
        if (leftDepth > rightDepth)
            return (leftDepth +1);
        else
            return (rightDepth +1);
    }
}
node* FindMin(node*root)
{
    if(root==NULL)
        return NULL;
    if(root->left!=NULL)
        return FindMin(root->left);
    else
        return root;
}
node* FindMax(node*root)
{
    if(root==NULL)
        return NULL;
    if(root->right!=NULL)
        return FindMax(root->right);
    else
        return root;
}

node* successor(node* root,char* x)
{
    node*current= searchrecursive(root,x);
    if(current == NULL)
        return NULL;
    if(current->right != NULL)
    {
        return FindMin(current->right);
    }
    else
    {
        node* successor = NULL;
        node* ancestor = root;
        while(ancestor != current)
        {
            if(strcasecmp(current->data, ancestor->data)<0)
            {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else
                ancestor = ancestor->right;
        }
        return successor;
    }
}
node* predecessor( node* root,char* x)
{
    node* current = searchrecursive(root,x);
    if(current == NULL)
        return NULL;
    if(current->left != NULL)
    {
        return FindMax(current->left);
    }
    else
    {
        node* predecessor = NULL;
        node* ancestor = root;
        while(ancestor != current)
        {
            if(strcasecmp(current->data, ancestor->data)>0)
            {
                predecessor = ancestor;
                ancestor = ancestor->right;
            }
            else
                ancestor = ancestor->left;
        }
        return predecessor;
    }
}
void ReadDictionary(char* filename)
{
    FILE *f1;
    char c[70];
    f1=fopen(filename,"r");
    while(!feof(f1))
    {


        fscanf(f1, "%[^\n] ", c) ;

        mainRoot=insert(mainRoot,c);

    }
    fclose(f1);


}
int main()
{
    char input[256] = "";

    puts("----------------------------------");
    ReadDictionary("EN-US-Dictionary.txt");
    puts("Dictionary Loaded Successfully...!");
    puts("----------------------------------");
    printf("Size = %d\n",count(mainRoot));
    puts("----------------------------------");
    printf("Height = %d\n",Height(mainRoot));
    puts("----------------------------------");

    printf("Enter a sentence :\n");
    gets(input);
    char*tok=strtok(input," ");
    node* se;




    while(tok!=NULL)
    {
        se=searchrecursive(mainRoot,tok);
        if(se==NULL)
        {
            node*n = nodeBeforeNull(mainRoot,tok);
            node * suc = successor(mainRoot,n->data);
            node * pre = predecessor(mainRoot,n->data);
            printf("%s -INCORRECT, Suggestions : %s, %s, %s\n",tok,n->data,suc->data,pre->data);
        }
        else
            printf("%s -CORRECT\n",tok);
        tok=strtok(NULL," ");

    }


    return 0;

}
