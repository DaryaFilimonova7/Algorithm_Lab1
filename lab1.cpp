// внутри функций не должно быть печати
// дб возвращен результат, который можно где-то использовать
// как ошибку можно вернуть -1, но лучше исп-ть Exception try{} catch{}

#include <iostream>

// односвязный список
class Node
{
public:
    int data;
    class Node* next;
};

class List
{
    // Указатели на первый и последний эл-ты списка
    Node *first;
    Node *last;

public:
    // Инициализация списка
    List()
    {
        // указатели на первый и последний эл-ты списка
        first = nullptr;
        last = nullptr;
    }

    // ссылка на ф-ию добавления элемента в конец/начало списка
    Node* add_first(int);
    Node* add_last(int);
    Node* add_position(int,int);
    void delete_value(int);
    void delete_position(int);
    Node* search_value(int);
    Node* search_position(int);
    void print_list();
};


Node* List :: add_first(int number)
{
    Node *element = new Node();
    element->data = number; // помещаем число в data этого узла

    // если список пустой
    if (first == nullptr)
    {
        element->next = nullptr; // обозначаем, что этот узел ни на что не указывает
        first = element;
        last = element;
    }
    else
    {
        element->next = first; // за новым элеменом следует тот, что был началом
        first = element; // теперь element принимает статус первого
    }
    return element;

}

Node* List :: add_last(int number)
{
    Node *element = new Node();
    element->data = number; // помещаем число в data этого узла
    element->next = nullptr; // обозначаем, что этот узел ни на что не указывает

    // если список пустой
    if (first == nullptr)
    {
        first = element;
        last = element;
    }
    else
    {
        last->next = element; // узел, который до этого был последним, теперь указывает не на nullptr, а на созданный element
        last = element; // теперь element принимает статус последнего
    }
    return element;
}

Node* List :: add_position(int number, int position)
{
    Node *element = new Node();
    // добавление первого элемента
    if (position == 0)
    {
        add_first(number);
    }

    else
    {
        Node *before_element = search_position(position-1);
        // добавление последнего элемента
        if (before_element == last)
        {
            add_last(number);
        }
        // добавление любого другого элемента
        else
        {
            element->data = number;

            // вкладываем в element ссылку на следующий, которую берем из i-1 элемента
            element->next = before_element->next;
            // в i-1 заменяем ссылку на element
            before_element->next = element;
        }
    }
    return element;
}

void List :: delete_value(int value)
{
    Node *element = first;
    if (first->data == value)
    {
        first = element->next;
        delete element;
    }
    else
    {
        if (last->data == value)
        {
            while (element->next != last) {element = element->next;}
            // предпоследний эл-т
            element->next = nullptr;
            delete last;
            last = element;
        }
        else
        {
            Node *before_element = first;
            element = first->next;
            // перебор элементов
            while (element->data != value)
            {
                before_element = before_element->next;
                element = before_element->next;
            }

            before_element->next = element->next;
            delete element;
        }
    }
}

void List :: delete_position(int position)
{
    Node *element = new Node();
    // удаление первого элемента
    if (position == 0)
    {
        element = first;
        first = element->next;
        delete element;
    }
    // удаление любого другого элемента
    else
    {
        Node *before_element = search_position(position-1);
        element = before_element->next;
        if (element == last)
        {
            before_element->next = nullptr;
            delete last;
            last = before_element;
        }
        else
        {
            before_element->next = element->next;
            delete element;
        }
    }
}

Node* List :: search_value(int value)
{
    Node *x = first;
    while (x->data != value)
    {
        x = x->next;
        if (x == nullptr)
        {
            return nullptr;
        }
    }
    return x;
}

Node* List :: search_position(int position)
{
    Node *x = first;
    for (int i = 0; i<position;i++)
    {
        x = x->next;
        if (x == nullptr)
        {
            return nullptr;
        }
    }
    return x;
}

void List :: print_list()
{
    if (first == nullptr)
    { std::cout << "The list is empty." << std::endl; }
    else
    {
        Node *x = first;
        while (x != nullptr)
        {
            std::cout << x->data << " ";
            x = x->next;
        }
        std::cout << std::endl;
    }
}


int main() {

    // Создание списка
    List list;
    std::cout << std::endl;
    // Исходное состояние
    list.print_list();

    std::string option;
    std::cout << "\n Choose option: \n a1 - add an element to the beginning \n a2 - add an element to the end \n b - add an element to a curtain position \n c - delete element with a curtain value \n d - delete element with a curtain position \n e - search for element with a curtain value \n f - search for element with a curtain position \n g - print all elements \n s - stop " << std::endl;
    while (option != "s" && std::cin.good()) {      
        std::cin >> option;
        int value;
        int position;
        if (option == "a1") {
            std::cout << "Enter value: ";
            std::cin >> value;
            list.add_first(value);
            std::cout << "[ " << value << " ] added to the beginning" << std::endl;
            std::cout << "Choose option. " << std::endl;
        }
        else if (option == "a2") {
            std::cout << "Enter value: ";
            std::cin >> value;
            list.add_last(value);
            std::cout << "[ " << value << " ] added to the end" << std::endl;
            std::cout << "Choose option. " << std::endl;
        } else if (option == "b") {
            std::cout << "Enter value: ";
            std::cin >> value;
            std::cout << "Enter position: ";
            std::cin >> position;
            list.add_position(value, position);
            std::cout << "[ " << value << " ] added to position " << position << std::endl;
            std::cout << "Choose option. " << std::endl;
        } else if (option == "c") {
            std::cout << "Enter value: ";
            std::cin >> value;
            if (list.search_value(value) == nullptr)
            {
                std::cout << "No element with this value." << std::endl;
            }
            else
            {
                list.delete_value(value);
                std::cout << "Element is deleted." << std::endl;
            }
            std::cout << "Choose option. " << std::endl;
        } else if (option == "d") {
            std::cout << "Enter position: ";
            std::cin >> position;
            if (list.search_position(position) == nullptr)
            {
                std::cout << "No element in this position." << std::endl;
            }
            else
            {
                list.delete_position(position);
                std::cout << "Element is deleted." << std::endl;
            }
            std::cout << "Choose option. " << std::endl;
        } else if (option == "e") {
            std::cout << "Enter value: ";
            std::cin >> value;
            if (list.search_value(value) == nullptr)
            {
                std::cout << "No element with this value." << std::endl;
            }
            else
            {
                std::cout << "[ " << list.search_value(value)->data << " ] is found " << std::endl;
            }
            std::cout << "Choose option. " << std::endl;
        } else if (option == "f") {
            std::cout << "Enter position: ";
            std::cin >> position;
            if (list.search_position(position) == nullptr)
            {
                std::cout << "No element in this position." << std::endl;
            }
            else
            {
                std::cout << "[ " << list.search_position(position)->data << " ] is found in position " << position << std::endl;
                std::cout << "Choose option. " << std::endl;
            }
        } else if (option == "g") { list.print_list(); std::cout << "Choose option. " << std::endl;}
        else if (option == "s") { std::cout << std::endl; }
        else { std::cout << "Incorrect option" << std::endl; }
    }


    return 0;
}
