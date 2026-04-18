#include <bits/stdc++.h>
using namespace std;

struct Product
{
    int id;
    char name[30];
    float price;
    int qty;
    Product* next;
};

Product* head = NULL;

Product* hashTable[1000] = {NULL};

struct Action
{
    char type[10];
    Product data;
};

Action undoStackArr[100];
int top = -1;

Product* create(int id, char name[], float price, int qty)
{
    Product* p = new Product;

    p->id = id;
    strcpy(p->name, name);
    p->price = price;
    p->qty = qty;
    p->next = NULL;

    return p;
}

void push(Action a)
{
    undoStackArr[++top] = a;
}

void addProduct(int id, char name[], float price, int qty)
{
    Product* p = create(id, name, price, qty);

    if (head == NULL)
        head = p;
    else
    {
        Product* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = p;
    }

    hashTable[id] = p;

    Action a;
    strcpy(a.type, "ADD");
    a.data = *p;
    push(a);

    cout << "Added!\n";
}

void searchProduct(int id)
{
    if (hashTable[id] != NULL)
    {
        cout << "Found: " << hashTable[id]->name << endl;
    }
    else
    {
        cout << "Not found\n";
    }
}

void deleteProduct(int id)
{
    Product *temp = head, *prev = NULL;

    while (temp != NULL)
    {
        if (temp->id == id)
        {

            Action a;
            strcpy(a.type, "DELETE");
            a.data = *temp;
            push(a);

            hashTable[id] = NULL;

            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            delete temp;

            cout << "Deleted!\n";
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "Not found\n";
}

void showProducts()
{
    if (!head)
    {
        cout << "No products\n";
        return;
    }
    Product* arr[100];
    int n = 0;

    Product* temp = head;
    while (temp)
    {
        arr[n++] = temp;
        temp = temp->next;
    }
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j]->id > arr[j + 1]->id)
                swap(arr[j], arr[j + 1]);

    for (int i = 0; i < n; i++)
    {
        cout << "ID: " << arr[i]->id
             << ", Name: " << arr[i]->name
             << ", Price: " << arr[i]->price
             << ", Qty: " << arr[i]->qty << endl;
    }
}


void undo()
{
    if (top == -1)
    {
        cout << "Nothing to undo\n";
        return;
    }

    Action a = undoStackArr[top--];

    if (strcmp(a.type, "ADD") == 0)
    {
        deleteProduct(a.data.id);
    }
    else if (strcmp(a.type, "DELETE") == 0)
    {
        addProduct(a.data.id, a.data.name, a.data.price, a.data.qty);
    }

    cout << "Undo done\n";
}

int main()
{
    int choice, id, qty;
    float price;
    char name[30];

    while (1)
    {
        cout << "                  Welcome to BUBT General Store\n1.Add\n2.Show\n3.Search\n4.Delete\n5.Undo\n6.Exit\n";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter ID, name, price and quantity: ";
            cin >> id >> name >> price >> qty;
            addProduct(id, name, price, qty);
            break;

        case 2:
            showProducts();
            break;

        case 3:
            cout << "Enter id: ";
            cin >> id;
            searchProduct(id);
            break;

        case 4:
            cout << "Enter id: ";
            cin >> id;
            deleteProduct(id);
            break;

        case 5:
            undo();
            break;

        case 6:
            return 0;
        }
    }
}
