typedef struct Node {
    int value;
    int row;
    int col;
    struct Node* next;
} Node;


Node* createNode(int value, int row, int col) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL;
    return newNode;
}

void insert_node(Node **head, int row, int col, int val) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->row = row;
    new_node->col = col;
    new_node->value = val;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
}
// Function to load a matrix from .dat files

Node* loadtxt(char *str) {
    FILE *fp = fopen(str, "r");
    Node* head = NULL;
    Node* currentRow = NULL;

    int numRows = 3;
    int numCols = 1;

    // Loop through each row
    for (int i = 0; i < numRows; i++) {
        Node* newRow = NULL;
        Node* currentCol = NULL;

        // Loop through each column in the current row
        for (int j = 0; j < numCols; j++) {
            int value;
            fscanf(fp,"%d", &value);

            
                Node* newNode = createNode(value, i, j);
                if (newRow == NULL) {
                    newRow = newNode;
                    currentCol = newNode;
                } else {
                    currentCol->next = newNode;
                    currentCol = newNode;
                }
            
        }

        if (newRow != NULL) {
            if (head == NULL) {
                head = newRow;
                currentRow = newRow;
            } else {
                currentRow->next = newRow;
                currentRow = newRow;
            }
        }
    }
    fclose(fp);
    return head;
}



//Function to create a matrix using linked lists
Node* createMatrix(int numRows, int numCols) {
    Node* head = NULL;
    Node* currentRow = NULL;

    // Loop through each row
    for (int i = 0; i < numRows; i++) {
        Node* newRow = NULL;
        Node* currentCol = NULL;

        // Loop through each column in the current row
        for (int j = 0; j < numCols; j++) {
            int value;
            printf("Enter the value at position (%d,%d): ", i, j);
            scanf("%d", &value);

            // If the value is not 0, create a new node and add it to the matrix
            if (value != 0) {
                Node* newNode = createNode(value, i, j);
                if (newRow == NULL) {
                    newRow = newNode;
                    currentCol = newNode;
                } else {
                    currentCol->next = newNode;
                    currentCol = newNode;
                }
            }
        }

        // If the current row is not empty, add it to the matrix
        if (newRow != NULL) {
            if (head == NULL) {
                head = newRow;
                currentRow = newRow;
            } else {
                currentRow->next = newRow;
                currentRow = newRow;
            }
        }
    }

    return head;
}


void print(Node* head,int numRows,int numCols) {

    
    for (Node* curr = head; curr != NULL; curr = curr->next) {
        if (curr->row >= numRows) {
            numRows = curr->row + 1;
        }
        if (curr->col >= numCols) {
            numCols = curr->col + 1;
        }
    }
    

    // Loop through each row in the matrix
    for (int i = 0; i < numRows; i++) {
        // Loop through each column in the matrix
        for (int j = 0; j < numCols; j++) {

            Node* curr = head;
            while (curr != NULL && (curr->row < i || (curr->row == i && curr->col < j))) {
                curr = curr->next;
            }
            if (curr != NULL && curr->row == i && curr->col == j) {
                printf("%d ", curr->value);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}


// Function for finding the Transpose of the matrix

Node* transpose(Node* head) {
    Node* transposeHead = NULL;
    
    // Loop through each node in the original linked list
    for (Node* curr = head; curr != NULL; curr = curr->next) {
        // Create a new node with its row and column positions swapped
        Node* newNode = createNode(curr->value, curr->col, curr->row);
        
        if (transposeHead == NULL) {
            transposeHead = newNode;
        } else {
            Node* currTranspose = transposeHead;
            while (currTranspose->next != NULL) {
                currTranspose = currTranspose->next;
            }
            currTranspose->next = newNode;
        }
    }
    
    return transposeHead;
}


// Function to multiply two matrices
Node* matmul(Node* A, Node* B, int numRowsA, int numColsB) {
    // Create a new empty linked list for the result
    Node* resultHead = NULL;
    
    // Loop through each row in A
    for (int i = 0; i < numRowsA; i++) {
        // Loop through each column in B
        for (int j = 0; j < numColsB; j++) {
            int dotProduct = 0;
        
            for (Node* currA = A; currA != NULL && currA->row == i; currA = currA->next) {
                for (Node* currB = B; currB != NULL && currB->col == j; currB = currB->next) {
                    if (currA->col == currB->row) {
                        dotProduct += currA->value * currB->value;
                    }
                }
            }
            if (dotProduct != 0) {
                Node* newNode = createNode(dotProduct, i, j);
                if (resultHead == NULL) {
                    resultHead = newNode;
                } else {
                    Node* prev = NULL;
                    Node* currR = resultHead;
                    while (currR != NULL && (currR->row < newNode->row || (currR->row == newNode->row && currR->col < newNode->col))) {
                        prev = currR;
                        currR = currR->next;
                    }
                    if (prev == NULL) {
                        resultHead = newNode;
                    } else {
                        prev->next = newNode;
                    }
                    newNode->next = currR;
                }
            }
        }
    }
    
    
    return resultHead;
}


// Function for multiplying the matrix with the float value

Node* mat_val(Node* head, double scalar) {
    // Loop through each node in the linked list
    for (Node* curr = head; curr != NULL; curr = curr->next) {
        // Multiply the value of the node with the scalar
        double result = scalar * curr->value;
        
        curr->value = result;
    }
    
    return head;
}


// Function for moving the element of matrix to the double vaue

double get(Node* head, int row, int col) {
    double result = 0.0;
    
    if (head == NULL) {
        printf("Error: matrix is empty\n");
        return result;
    }
    
    Node* curr = head;
    while (curr != NULL && (curr->row != row || curr->col != col)) {
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Error: element not found in matrix\n");
        return result;
    }
    
    result = (double) curr->value;
        
    return result;
}


// Function for saving the matrix into a .dat file
void save(char *filename, Node* head, int numRows, int numCols) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    // Loop through each row
    for (int i = 0; i < numRows; i++) {
        Node* current = head;
        int j = 0;

        // Loop through each column in the current row
        while (current != NULL && current->row == i) {
            // Fill in any missing values with 0
            while (j < current->col) {
		    fprintf(fp, "%d ", 0);
                j++;
            }

            // Write the value of the current node to the file
            fprintf(fp, "%d ", current->value);
            j++;
            current = current->next;
        }

        // Fill in any remaining empty columns with 0
        while (j < numCols) {
            fprintf(fp, "%d ", 0);
            j++;
        }

        // Add a newline character at the end of each row
        fprintf(fp, "\n");
    }

    fclose(fp);
}


//Function for addition
Node *linalg_add(Node *a, Node *b) {
    Node *result = NULL;

    while (a != NULL && b != NULL) {
        if (a->row < b->row || (a->row == b->row && a->col < b->col)) {
            insert_node(&result, a->row, a->col, a->value);
            a = a->next;
        } else if (a->row == b->row && a->col == b->col) {
            int val = a->value + b->value;
            if (val != 0) {
                insert_node(&result, a->row, a->col, val);
            }
            a = a->next;
            b = b->next;
        } else {
            insert_node(&result, b->row, b->col, b->value);
            b = b->next;
        }
    }

    while (a != NULL) {
        insert_node(&result, a->row, a->col, a->value);
        a = a->next;
    }

    while (b != NULL) {
        insert_node(&result, b->row, b->col, b->value);
        b = b->next;
    }

    return result;
}


//Defining cross product

Node* cross_prod(Node* a, Node* b, int numRowsa, int numColsb) {
    
    // Create a new linked list to store the result
    Node* resultHead = NULL;


   // Loop through each row in A    
 for (int i = 0; i < numRowsa; i++) {   
   // Loop through each column in B    
 for (int j = 0; j < numColsb; j++) { 
	  int dotProduct = 0;



    // Compute the cross product
    int x = a->value * b->next->value - a->next->value * b->value;
    int y = a->next->value * b->next->next->value - a->next->next->value * b->next->value;
    int z = a->next->next->value * b->value - a->value * b->next->next->value;

    // Add the non-zero elements to the result linked list
    if (x != 0) {
        Node* newNode = createNode(x, 0, 0);
        newNode->next = resultHead;
        resultHead = newNode;
    }

    if (y != 0) {
        Node* newNode = createNode(y, 1, 0);
        newNode->next = resultHead;
        resultHead = newNode;
    }

    if (z != 0) {
        Node* newNode = createNode(z, 2, 0);
        newNode->next = resultHead;
        resultHead = newNode;
    }

    return resultHead;
}}}

Node* cross_prod1(Node* e2,Node* e3){
	Node *k,*p,*result,*a,*b;
	int a0,a1,a2;
	a=e2,b=e3;
	result=NULL;
	a0=(a->next->value)*(b->next->next->value);
	a=e2,b=e3;
	a0-=(a->next->next->value)*(b->next->value);
	insert_node(&result,0,0,a0);
	a1=(a->next->next->value)*(b->value);
	a=e2,b=e3;
	a1-=(a->value)*(b->next->next->value);
	insert_node(&result,1,0,a1);
	a2=(a->value)*(b->next->value);
	a=e2,b=e3;
	a2-=(a->next->value)*(b->value);
	insert_node(&result,2,0,a2);
	return result;
	
}

	
