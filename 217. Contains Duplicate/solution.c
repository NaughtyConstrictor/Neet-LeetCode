// sol2

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define ABS(X) ( ( (X) >= 0 )? (X) : -(X) )
#define HASH(X, CAPACITY) ( (ABS(X)) % (CAPACITY) ) 


// hash set implementation

typedef struct node {
    int value;
    struct node *next;
} Node;

typedef struct linked_list {
    Node *head;
} LinkedList;

typedef struct array {
    int capacity;
    int size;
    int *array;
} Array;

typedef struct set {
    int capacity;
    int size;
    Array * hash_indices;
    LinkedList **arr;
} Set;


Node * create_node(int value)
{
    Node *node = malloc(sizeof *node);
    if (node == NULL)
        return NULL;
    
    node->value = value;
    node->next = NULL;
    return node;
}


void free_node(Node * node)
{
    free(node);
}


LinkedList * create_linked_list()
{
    LinkedList *list = malloc(sizeof *list);
    
    if (list == NULL)
        return NULL;
    
    list->head = NULL;
    return list;
}


void free_linked_list(LinkedList * list)
{
    Node *head = list->head;
    Node *temp = head;
    while (head)
    {
        head = head->next;
        free(temp);
        temp = head;
    }
    free(list);
}


void list_append(LinkedList * list, int value)
{
    Node *node = create_node(value);
    if (node == NULL)
        return;
    node->next = list->head;
    list->head = node;
}


int search_list(LinkedList * list, int value)
{
    if (list == NULL)
        return -1;

    Node *current = list->head;
    for (int i = 0; current; ++i)
    {
        if (current->value == value)
            return i;
        current = current->next;
    }

    return -1;
}


Array * create_array()
{
    Array *arr = malloc(sizeof *arr);
    if (arr == NULL)
        return NULL;
    
    arr->capacity = 8;
    arr->size = 0;
    int *temp = malloc(sizeof(*temp) * arr->capacity);
    if (temp == NULL)
        return NULL;
    arr->array = temp;

    return arr;
}


void free_array(Array * arr)
{
    free(arr->array);
    free(arr);
}


void resize_array(Array * arr)
{
    arr->capacity = (int)(arr->capacity * 1.5);
    int *new_arr = realloc(arr->array, sizeof(*new_arr) * arr->capacity);
    if (new_arr == NULL)
        return;
    arr->array = new_arr;
}


void array_append(Array * arr, int value)
{
    arr->array[arr->size] = value;
    ++(arr->size);
    if (arr->size >= (int)(arr->capacity * 0.8))
        resize_array(arr);
}


Set * create_set() {
    Set *new_set = malloc(sizeof *new_set);
    if (new_set == NULL)
        return NULL;
    
    new_set->capacity = 8;
    new_set->size = 0;
    
    Array *temp_arr = create_array();
    if (temp_arr == NULL)
        return NULL;
    new_set->hash_indices = temp_arr;

    LinkedList **temp = calloc(new_set->capacity, sizeof *temp);
    if (temp == NULL)
        return NULL;
    new_set->arr = temp;

    return new_set;
}


void free_set(Set * set)
{
    for (int i = 0; i < set->capacity; ++i)
    {
        LinkedList * list = set->arr[i];
        // I can remove this check right? because free(NULL) is fine?
        if (list == NULL)
            continue;
        free(list);
    }

    free_array(set->hash_indices);
    free(set->arr);
    free(set);
}


void resize_set(Set * set)
{
    set->capacity = (int)(set->capacity * 1.5);
    LinkedList **new_arr = calloc(set->capacity, sizeof *new_arr);
    if (new_arr == NULL)
        return;

    Array *new_indices = create_array();
    for (int i = 0; i < set->hash_indices->size; ++i)
    {
        const int index = set->hash_indices->array[i];
        LinkedList *list = set->arr[index];
        Node *current = list->head;
        while (current)
        {
            const int index = HASH(current->value, set->capacity);
            
            if (new_arr[index] == NULL)
            {
                new_arr[index] = create_linked_list();
                array_append(new_indices, index);
            }
            
            list_append(new_arr[index], current->value);

            current = current->next;
        }
    }

    set->hash_indices = new_indices;
    set->arr = new_arr;
}


void add(Set * set, int value)
{
    const int index = HASH(value, set->capacity);
    LinkedList **list = &(set->arr[index]);

    if (*list == NULL)
    {
        *list = create_linked_list();
        array_append(set->hash_indices, index);
    }
    
    if (search_list(*list, value) == -1)
    {
        list_append(*list, value);
        ++(set->size);
    }

    if (set->size >= (int)(set->capacity * 0.8))
        resize_set(set); 
}

bool contains(Set *set, int value)
{
    const int index = HASH(value, set->capacity);
    LinkedList *list = set->arr[index];
    
    if (list == NULL)
        return false;
    
    Node *current = list->head;
    while (current)
    {
        if (current->value == value)
            return true;
        current = current->next;
    }

    return false;
}

bool containsDuplicate(int *nums, int nums_size) {
    Set *seen = create_set(); 
   
    for (int i = 0; i < nums_size; ++i)
    {
        const int value = nums[i];
        if (contains(seen, value))
            return true;
        add(seen, value);
    }
   
    free_set(seen);
    return false;
}


void print(LinkedList *list)
{
    Node *node = list->head;
    while (node)
    {
        printf("%d, ", node->value);
        node = node->next;
    }
    putchar('\n');
}

void print_set(Set *set)
{
    for (int i = 0; i < set->capacity; ++i)
    {
        printf("%i: ", i);
        if (set->arr[i] == NULL)
        {
            printf("NULL\n");
            continue;
        }
        print(set->arr[i]);
    }
}


int main(void)
{
    Set *set = create_set();
    add(set, 1);
    add(set, 2);
    add(set, 3);
    add(set, 4);
    add(set, 1);
    add(set, 2);
    add(set, 3);
    add(set, 4);
    add(set, 11);
    add(set, 22);
    add(set, 33);
    add(set, 44);
    add(set, 10);
    add(set, 20);
    add(set, 30);
    add(set, 40);
    print_set(set);
}



// sol1

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int compare_func(const void * ptr1, const void * ptr2)
{
    return *(int*)ptr1 - *(int*)ptr2;
}

bool containsDuplicate(int* nums, int nums_size) {
    const size_t num_bytes = sizeof(*nums) * nums_size;
    int * sorted_nums = malloc(num_bytes);
    memcpy(sorted_nums, nums, num_bytes);
    qsort(sorted_nums, nums_size, sizeof *sorted_nums, compare_func);
    for (int i = 1; i < nums_size; ++i) {
        if (sorted_nums[i] == sorted_nums[i - 1])
            return true;
    }
    return false;
}