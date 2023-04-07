#include <stdio.h>
#include <string.h>

struct GroceryItem {
    char name[50];
    float price;
    int quantity;
};

void addNewItem(struct GroceryItem items[], int *count) {
    printf("Enter item name: ");
    scanf("%s", items[*count].name);
    printf("Enter item price: ");
    scanf("%f", &items[*count].price);
    printf("Enter item quantity: ");
    scanf("%d", &items[*count].quantity);
    (*count)++;
}

void displayItems(struct GroceryItem items[], int count) {
    printf("%-30s %-10s %-10s\n", "Item Name", "Price", "Quantity");
    for (int i = 0; i < count; i++) {
        printf("%-30s %-10.2f %-10d\n", items[i].name, items[i].price, items[i].quantity);
    }
}

void searchItem(struct GroceryItem items[], int count) {
    char searchName[50];
    int found = 0;

    printf("Enter item name or keyword to search for: ");
    scanf("%s", searchName);

    printf("%-30s %-10s %-10s\n", "Item Name", "Price", "Quantity");
    for (int i = 0; i < count; i++) {
        if (strstr(items[i].name, searchName) != NULL) {
            printf("%-30s %-10.2f %-10d\n", items[i].name, items[i].price, items[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No items found.\n");
    }
}

void updateItem(struct GroceryItem items[], int count) {
    int choice;
    int index;

    printf("Enter item number to update: ");
    scanf("%d", &index);

    if (index >= count || index < 0) {
        printf("Invalid item number.\n");
        return;
    }

    printf("1. Update price\n");
    printf("2. Update quantity\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new price: ");
            scanf("%f", &items[index].price);
            break;
        case 2:
            printf("Enter new quantity: ");
            scanf("%d", &items[index].quantity);
            break;
        default:
            printf("Invalid choice.\n");
    }
}

void deleteItem(struct GroceryItem items[], int *count) {
    int choice;

    printf("Enter item number to delete: ");
    scanf("%d", &choice);

    if (choice >= *count || choice < 0) {
        printf("Invalid item number.\n");
        return;
    }

    for (int i = choice; i < *count - 1; i++) {
        strcpy(items[i].name, items[i+1].name);
        items[i].price = items[i+1].price;
        items[i].quantity = items[i+1].quantity;
    }

    (*count)--;
    printf("Item deleted.\n");
}

float calculateTotal(struct GroceryItem items[], int count) {
    float total = 0;

    for (int i = 0; i < count; i++) {
        total += items[i].price * items[i].quantity;
    }

    return total;
}

void saveItems(struct GroceryItem items[], int count) {
    FILE *fp;

    fp = fopen("grocery_items.txt", "w");
if (fp == NULL) {
printf("Error opening file.\n");
return;
}
for (int i = 0; i < count; i++) {
    fprintf(fp, "%s %0.2f %d\n", items[i].name, items[i].price, items[i].quantity);
}

printf("Items saved to file.\n");
fclose(fp);
}

void loadItems(struct GroceryItem items[], int *count) {
FILE *fp;
fp = fopen("grocery_items.txt", "r");
if (fp == NULL) {
    printf("Error opening file.\n");
    return;
}

while (!feof(fp)) {
    fscanf(fp, "%s %f %d\n", items[*count].name, &items[*count].price, &items[*count].quantity);
    (*count)++;
}

printf("Items loaded from file.\n");
fclose(fp);
}

int main() {
struct GroceryItem items[50];
int count = 0;
int choice;
loadItems(items, &count);

do {
    printf("\n1. Add new item\n");
    printf("2. Display all items\n");
    printf("3. Search for an item\n");
    printf("4. Update an item\n");
    printf("5. Delete an item\n");
    printf("6. Calculate total\n");
    printf("7. Save items to file\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addNewItem(items, &count);
            break;
        case 2:
            displayItems(items, count);
            break;
        case 3:
            searchItem(items, count);
            break;
        case 4:
            updateItem(items, count);
            break;
        case 5:
            deleteItem(items, &count);
            break;
        case 6:
            printf("Total cost: %.2f\n", calculateTotal(items, count));
            break;
        case 7:
            saveItems(items, count);
            break;
        case 8:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice.\n");
    }
} while (choice != 8);

return 0;
}
