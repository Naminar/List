
#include "list.h"

void list_init(Tree* tree, size_t capacity)
{
    assert(tree && capacity > 0);

    tree->lst = (List*) calloc(capacity + 1, sizeof (List));

    assert(tree->lst);

    tree->capacity = capacity;

    tree->size = 0;

    for (long long int ind = 1; ind < capacity; ind++)
    {
        tree->lst[ind].next = 0 - (ind + 1);
    }

    tree->lst[capacity].next = 0;

    tree->lst[1].prev = 0;

    for (long long int ind = 2; ind <= capacity; ind++)
    {
        tree->lst[ind].prev = 1 - ind;
    }

    tree->free = -1;

    tree->sort_flag = false;
}

size_t list_insert(Tree* tree, long long int num, type value)
{
    assert(tree && num >= 0 && tree->free < 0 && num <= tree->size);

    tree->sort_flag = false;

    ++tree->size;

    long long int next_cell = 0;

    for (long long int ind = 0; ind < num; ind++)
    {
         next_cell = NEXT_OF_NEXT_CELL;
    }

    num = next_cell;

    tree->lst[0 - tree->free].data = value;

    if (tree->lst[num].next == 0)
        tree->lst[0].prev = 0 - tree->free;

    long long int free_cell = tree->free;

    tree->free = tree->lst[0 - tree->free].next;

    //for empty cell _ field prev is zero
    //===========================================

    if (tree->free)
        tree->lst[0 - tree->free].prev = 0;

    //===========================================

    tree->lst[tree->lst[num].next].prev = 0 - free_cell;

    tree->lst[0 - free_cell].next = tree->lst[num].next;

    tree->lst[0 - free_cell].prev = num;

    tree->lst[num].next = 0 - free_cell;

    return 1;
}

size_t list_delete_after(Tree* tree, long long int num)
{
    assert(tree && num >= 0);

    assert(num < tree->size);

    tree->sort_flag = false;

    --tree->size;

    long long int next_cell = 0;

    for (long long int ind = 0; ind < num; ind++)
    {
         next_cell = NEXT_OF_NEXT_CELL;
    }

    num = next_cell;

    next_cell = DOUBLE_NEXT;

    long long int free_cell = 0 - tree->lst[num].next;

    if (next_cell == 0)
    {
        tree->lst[0].prev = num;
    }

    tree->lst[tree->lst[num].next].prev = 0;

    DOUBLE_NEXT = tree->free;

    tree->lst[num].next = next_cell;

    tree->lst[next_cell].prev = num;

    if (tree->free)
        tree->lst[0 - tree->free].prev = free_cell;

    tree->free = free_cell;

    return 1;
}

void do_list_linearization(Tree* tree, const char *const password)
{
    assert(tree);

    if(strcmp(password, tree->password))
    {
        printf("$100 is transferred to the developer's account.\n"
               "\t\tGod bless you!\n\n");
        return;
    }
    else if (tree->lst[0].prev == 0)
    {
        printf("Please, insert one element.\n");

        return;
    }

    printf("Linearization started.\n");

    List list_tmp = {};

    long long int s_ind = 0;

    long long int next_cell  = tree->lst[0].next;

    for (s_ind = 0; s_ind < tree->capacity; s_ind++)
    {
        if (!next_cell)
            break;

        if (tree->lst[s_ind + 1].next + tree->lst[s_ind + 1].prev >= 0 )
        {
            list_tmp = tree->lst[s_ind + 1];

            tree->lst[tree->lst[s_ind + 1].prev].next = next_cell;
        }
        else
        {
            list_tmp  = marker_list;
        }

        tree->lst[s_ind + 1] = tree->lst[next_cell];

        tree->lst[next_cell] = list_tmp;

        next_cell  = tree->lst[s_ind + 1].next;

        tree->lst[s_ind + 1].next = s_ind + 2;

        tree->lst[s_ind + 1].prev = s_ind ;
    }

    tree->lst[s_ind].next = 0;

    /////////////////////////

    tree->lst[0].prev = s_ind;

    tree->lst[0].next = 1;

    tree->sort_flag = true;

    /////////////////////////

    for (long long int key = ++s_ind; key <= (long long int ) tree->capacity; key++)
    {
        tree->lst[key].prev =  1 - key;

        tree->lst[key].next = -1 - key;

        tree->lst[key].data = 0;
    }

    if (s_ind > tree->capacity)
        tree->free = 0;
    else
    {
        tree->free = 0 - s_ind;

        tree->lst[s_ind].prev = 0;
    }

    tree->lst[tree->capacity].next = 0;

    printf("Linearization done.\n");
}

long long int search_element(Tree* tree, long long int s_index)
{
    assert(tree && s_index > 0);

    long long int next_cell = 0;

    for (long long int key_index = 0; key_index < s_index; key_index++)
    {
        next_cell = NEXT_OF_NEXT_CELL;
    }

    return next_cell;
}

void list_destructor(Tree* tree)
{
    assert(tree);

    tree->free      = 0;

    tree->capacity  = 0;

    tree->sort_flag = 0;

    tree->size      = 0;

    free(tree->lst);
}

void list_dump(Tree* tree)
{
    assert(tree);

    long long int next_cell = tree->lst[0].next;

    FILE* dump = fopen("dump.dot", "w");

    fprintf
    (
        dump,

        "digraph G{\n rankdir=\"LR\" \n size=\"100\" "

        "node [shape = record, fontname=Arial];\n     "
    );

    fprintf
    (
        dump,

        "struct1 [label =\" "
        "<f0> lst ptr               \\n %p  |"
        "<f1> linearization password\\n %s  |"
        "<f2> max capacity          \\n %u  |"
        "<f3> first free cell       \\n %lld|"
        "<f4> linearization flag    \\n %d   "
        "\\n-------------------------------- "
        "\\n0 - not sorted\\l1 - sorted\\l  |"
        "<f5> occupied cells number \\n %u  \"];"

        "struct1:f0 -> elem0;",

        tree->lst,      tree->password,     tree->capacity,
        0 - tree->free, tree->sort_flag,    tree->size
    );

    while (next_cell)
    {
        fprintf
        (
            dump,

            "elem%lld -> elem%lld;  "
            "elem%lld[label = \" {  "
            "value  \\n %d  |       "
            "next   \\n %lld|       "
            "prev   \\n %lld        "
            "} \"];\n",

            next_cell,                          NEXT_OF_NEXT_CELL,
            NEXT_OF_NEXT_CELL,                  tree->lst[NEXT_OF_NEXT_CELL].data,
            tree->lst[NEXT_OF_NEXT_CELL].next,  tree->lst[NEXT_OF_NEXT_CELL].prev
        );

        next_cell = NEXT_OF_NEXT_CELL;
    }

    fprintf
    (
        dump,

        "elem%lld -> elem%lld;  "
        "elem%lld[label = \" {  "
        "value  \\n %d  |       "
        "next   \\n %lld|       "
        "prev   \\n %lld        "
        "} \"];\n",

        next_cell,                          NEXT_OF_NEXT_CELL,
        NEXT_OF_NEXT_CELL,                  tree->lst[NEXT_OF_NEXT_CELL].data,
        tree->lst[NEXT_OF_NEXT_CELL].next,  tree->lst[NEXT_OF_NEXT_CELL].prev
    );

    next_cell = NEXT_OF_NEXT_CELL;

    /////////////////////////

    fprintf(dump, "}");

    fclose(dump);

    system ("dot dump.dot -Tpdf -o dump.pdf");

    system("dump.pdf");
}

//===============================================

/*int main(void)
{
    Tree der = {"my"}; //init your password;

    size_t capacity = 5;

    list_init(&der, capacity);

    list_insert(&der, 0, 1);
    list_insert(&der, 1, 2);
    list_insert(&der, 2, 3);
    list_insert(&der, 3, 4);
    list_insert(&der, 4, 55);

    //list_delete_after(&der, 1);
    //list_delete_after(&der, 1);
    //list_delete_after(&der, 1);//

    do_list_linearization(&der, "my"); //Confirm the password

    list_delete_after(&der,1);

    printf("$$ %lld $$\n", der.free);

    //list_insert(&der, 1, 2);

    printf("$$ %lld $$\n", der.free);//search_element(&der, 2));

    for (int ind = 0; ind <= capacity; ind++)
      printf("%d = %d__%lld__%lld\n", ind, der.lst[ind].data, der.lst[ind].next, der.lst[ind].prev);

    list_dump(&der);

    list_destructor(&der);

    return 0;
}//*/




