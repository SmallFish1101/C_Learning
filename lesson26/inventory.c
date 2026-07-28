#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    int  id;
    char name[32];
    int  quantity;
    float price;
} Product;

typedef struct {
    Product items[MAX_PRODUCTS];
    int     count;
} Inventory;

void inventory_init(Inventory *inv) {
    inv->count = 0;
}

int inventory_find(const Inventory *inv, int id) {
    for (int i = 0; i < inv->count; i++) {
        if (inv->items[i].id == id)
            return i;
    }
    return -1;
}

void inventory_add(Inventory *inv, int id, const char *name,
                   int quantity, float price) {
    if (inv->count >= MAX_PRODUCTS) return;
    Product *p = &inv->items[inv->count++];
    p->id = id;
    strcpy(p->name, name);
    p->quantity = quantity;
    p->price = price;
}

void inventory_list(const Inventory *inv) {
    if (inv->count == 0) {
        printf("  (empty)\n");
        return;
    }
    printf("  %-4s %-15s %-6s %s\n", "ID", "Name", "Qty", "Price");
    for (int i = 0; i < inv->count; i++)
        printf("  %-4d %-15s %-6d %.2f\n",
               inv->items[i].id, inv->items[i].name,
               inv->items[i].quantity, inv->items[i].price);
}

int main(void) {
    Inventory inv;
    inventory_init(&inv);

    inventory_add(&inv, 2001, "LED Red", 150, 0.25f);
    inventory_add(&inv, 2002, "LED Green", 80, 0.30f);
    inventory_add(&inv, 2003, "Resistor 220", 500, 0.05f);

    inventory_list(&inv);
    return 0;
}