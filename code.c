#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 100
#define FILENAME "inventory_data.txt"

struct Item {
    int code;
    char name[30];
    int quantity;
    float price;
};

struct Item inventory[MAX_ITEMS];
int itemCount = 0;

void printHeader(const char* title) {
    printf("\n=============================\n");
    printf("   %s\n", title);
    printf("=============================\n");
}

void saveInventoryToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error saving inventory to file.\n");
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%d %s %d %.2f\n", inventory[i].code, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }

    fclose(file);
    printf("Inventory saved to file successfully!\n");
}

void loadInventoryFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No previous inventory found. Starting fresh.\n");
        return;
    }

    itemCount = 0;
    while (fscanf(file, "%d %s %d %f", &inventory[itemCount].code, inventory[itemCount].name, &inventory[itemCount].quantity, &inventory[itemCount].price) != EOF) {
        itemCount++;
    }

    fclose(file);
    printf("Inventory loaded from file. %d items found.\n", itemCount);
}

void addItem() {
    printHeader("Add New Item");

    if (itemCount >= MAX_ITEMS) {
        printf("Inventory is full! Cannot add more items.\n");
        return;
    }

    struct Item newItem;
    printf("Enter item code: ");
    scanf("%d", &newItem.code);

    getchar(); // to consume leftover newline character

    printf("Enter item name: ");
    fgets(newItem.name, sizeof(newItem.name), stdin);
    newItem.name[strcspn(newItem.name, "\n")] = 0; // remove newline character from name

    printf("Enter item quantity: ");
    scanf("%d", &newItem.quantity);
    printf("Enter item price: ");
    scanf("%f", &newItem.price);

    inventory[itemCount] = newItem;
    itemCount++;

    printf("\nItem '%s' added successfully!\n", newItem.name);
    saveInventoryToFile();
}

void displayInventory() {
    printHeader("Inventory List");

    if (itemCount == 0) {
        printf("No items in the inventory.\n");
        return;
    }

    printf("%-10s %-20s %-10s %-10s\n", "Code", "Name", "Quantity", "Price");
    for (int i = 0; i < itemCount; i++) {
        printf("%-10d %-20s %-10d $%-9.2f\n", inventory[i].code, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

void searchItem() {
    printHeader("Search Item");

    if (itemCount == 0) {
        printf("No items in the inventory.\n");
        return;
    }

    int code;
    printf("Enter the item code to search: ");
    scanf("%d", &code);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].code == code) {
            printf("Item Found!\n");
            printf("Code: %d\nName: %s\nQuantity: %d\nPrice: $%.2f\n", inventory[i].code, inventory[i].name, inventory[i].quantity, inventory[i].price);
            return;
        }
    }

    printf("Item with code %d not found.\n", code);
}

void updateItem() {
    printHeader("Update Item");

    if (itemCount == 0) {
        printf("No items in the inventory.\n");
        return;
    }

    int code;
    printf("Enter the item code to update: ");
    scanf("%d", &code);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].code == code) {
            printf("Item Found!\n");
            printf("Updating details for item '%s'.\n", inventory[i].name);

            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Enter new price: ");
            scanf("%f", &inventory[i].price);

            printf("Item updated successfully!\n");
            saveInventoryToFile();
            return;
        }
    }

    printf("Item with code %d not found.\n", code);
}

void deleteItem() {
    printHeader("Delete Item");

    if (itemCount == 0) {
        printf("No items in the inventory.\n");
        return;
    }

    int code;
    printf("Enter the item code to delete: ");
    scanf("%d", &code);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].code == code) {
            printf("Item '%s' deleted successfully!\n", inventory[i].name);

            for (int j = i; j < itemCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }

            itemCount--;
            saveInventoryToFile();
            return;
        }
    }

    printf("Item with code %d not found.\n", code);
}

void displayMenu() {
    printHeader("Inventory Management System");
    printf("1. Add Item\n");
    printf("2. Display Inventory\n");
    printf("3. Search Item\n");
    printf("4. Update Item\n");
    printf("5. Delete Item\n");
    printf("6. Exit\n");
}

int main() {
    loadInventoryFromFile();

    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                searchItem();
                break;
            case 4:
                updateItem();
                break;
            case 5:
                deleteItem();
                break;
            case 6:
                printf("Exiting the system...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

        printf("\nPress Enter to continue...\n");
        getchar(); // Pause for user input
        getchar(); // For enter key buffer
    } while (choice != 6);

    return 0;
}