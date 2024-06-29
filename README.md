# Pawnshop Inventory Management System

A console-based application designed to efficiently manage the inventory of a pawnshop. This system allows users to add, edit, search, and delete items in the inventory using C and basic file handling.

## 🚀 Features

- **Add New Items** 🆕: Easily add new items with details like ID, name, category, condition, price, and date of pawn.
- **Edit Existing Items** ✏️: Modify item details based on their name to keep the inventory up-to-date.
- **Delete Items** 🗑️: Remove items from the inventory, with checks to prevent deletion of sold items.
- **Search Items** 🔍: Find items by name, date of pawn, or within a specific price range.
- **Category Display** 📂: View items grouped by their categories, such as Toys, Furniture, Decorations, Devices, and Tools.
- **Price Range Search** 💲: Identify items within a specified price range.
- **Date Search** 📅: Locate items based on their pawn date.

## 🛠️ How to Run

### Prerequisites

- A C compiler (e.g., GCC)
- Windows OS (for console-specific functions like `SetConsoleCursorPosition`)

### Installation

1. **Clone the Repository**: 
    ```bash
    git clone https://github.com/yourusername/Pawnshop-Inventory-Management-System.git
    ```
2. **Navigate to the Project Directory**:
    ```bash
    cd Pawnshop-Inventory-Management-System
    ```
3. **Compile the Code**:
    ```bash
    gcc -o pawnshop_inventory main.c
    ```
4. **Run the Application**:
    ```bash
    ./pawnshop_inventory
    ```

## 📋 Usage

### Add New Items
- Input the item details to add them to the inventory.

### Edit Items
- Select an item by name and edit any of its attributes.

### Delete Items
- Choose an item by name and remove it from the inventory, unless it is marked as sold.

### Search Items
- Use different search criteria (name, date, price range) to find specific items.

### Display Items by Category
- View items filtered by their respective categories.

📮 Feel free to customize this README further to suit your project's specific needs!
