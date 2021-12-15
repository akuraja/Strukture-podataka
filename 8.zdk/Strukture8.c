#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


struct _tree;
typedef struct _tree* treeP;
typedef struct _tree {
	int element;
	treeP left;
	treeP right;
} tree;

treeP InsertElement(int element, treeP root);
treeP CreateNewElement(int element);
int InorderPrint(treeP root);
int PreorderPrint(treeP root);
int PostorderPrint(treeP root);
treeP FindElement(int element, treeP root);
treeP FindMinElement(treeP root);
treeP DeleteElement(int element, treeP root);

int main()
{
	treeP root = NULL;
	treeP temp = NULL;
	root = InsertElement(7, root);
	root = InsertElement(1, root);
	root = InsertElement(9, root);
	root = InsertElement(13, root);
	root = InsertElement(5, root);
	root = InsertElement(6, root);
	root = InsertElement(8, root);
	root = InsertElement(9, root);
	root = InsertElement(2, root);
	root = InsertElement(42, root);
	InorderPrint(root);
	printf("\n");
	PreorderPrint(root);
	printf("\n");
	PostorderPrint(root);
	printf("\n");
	temp = FindElement(2, root);
	printf("%d\n", temp->element);
	root = DeleteElement(42, root);
	InorderPrint(root);
	printf("\n");
	return 0;
}

treeP InsertElement(int element, treeP root)
{
	treeP current = root;
	treeP newElement = NULL;

	if (current == NULL) {
		newElement = CreateNewElement(element);
		return newElement;
	}
	else if (element < current->element) {
		current->left = InsertElement(element, current->left);
	}
	else if (element > current->element) {
		current->right = InsertElement(element, current->right);
	}

	return current;
}

treeP CreateNewElement(int element)
{
	treeP newElement = NULL;

	newElement = (treeP)malloc(sizeof(tree));
	if (newElement == NULL) {
		printf("Can't allocate memory!\n");
		return NULL;
	}
	newElement->element = element;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

int InorderPrint(treeP root)
{
	treeP current = root;

	if (current != NULL) {
		InorderPrint(current->left);
		printf("%d ", current->element);
		InorderPrint(current->right);
	}

	return 0;
}

int PreorderPrint(treeP root)
{
	treeP current = root;

	if (current != NULL) {
		printf("%d ", current->element);
		PreorderPrint(current->left);
		PreorderPrint(current->right);
	}

	return 0;
}

int PostorderPrint(treeP root)
{
	treeP current = root;

	if (current != NULL) {
		PostorderPrint(current->left);
		PostorderPrint(current->right);
		printf("%d ", current->element);
	}

	return 0;
}

treeP FindElement(int element, treeP root)
{
	treeP current = root;

	if (current == NULL) {
		return NULL;
	}
	else if (element < current->element) {
		return FindElement(element, current->left);
	}
	else if (element > current->element) {
		return FindElement(element, current->right);
	}
	else {
		return current;
	}
}

treeP FindMinElement(treeP root)
{

	treeP current = root;

	while (current->left != NULL) {
		current = current->left;
	}

	return current;
}

treeP DeleteElement(int element, treeP root)
{
	treeP current = root;
	treeP temp = NULL;

	if (current == NULL) {
		printf("Ne postoji element koji zelite obrisati!\n");
		return current;
	}
	else if (element < current->element) {
		current->left = DeleteElement(element, current->left);
	}
	else if (element > current->element) {
		current->right = DeleteElement(element, current->right);
	}
	else if (current->left != NULL && current->right != NULL) {
		temp = FindMinElement(current->right);
		current->element = temp->element;
		current->right = DeleteElement(current->element, current->right);
	}
	else {
		temp = current;
		if (current->left == NULL) {
			current = current->right;
		}
		else {
			current = current->left;
		}
		free(temp);
	}

	return current;
}