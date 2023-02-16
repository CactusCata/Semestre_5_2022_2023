#include "instruction.h"

FILE *ramFile;

char *MEMORY_ARRAY_WRITTED_CASE_VAR_NAME = ".memWrittedCaseAmount";
const int ARRAY_START_LINE = 100;

// Emplacement de la mémoire de la machine RAM
int stackCursor = 1;

// Emplacement de code de la machine RAM
int codeCursor = 0;

// Table des identifiants de variables. Peut renvoyer un
// id.
ts table;

void freeTable() {
    ts_free_table(table);
}


void initMemoryArrayCursor() {
    /**
     * @brief Variable à l'intérieur de la machine RAM
     * qui contient la valeur du curseur ou l'utilisateur
     * peut écrire un tableau
     */
    ts_ajouter_id(table, MEMORY_ARRAY_WRITTED_CASE_VAR_NAME);
    LOAD_VALUE(ARRAY_START_LINE);
    STORE_VARIABLE(MEMORY_ARRAY_WRITTED_CASE_VAR_NAME);
}

void increaseMemoryVariableSize() {
    LOAD_VARIABLE(MEMORY_ARRAY_WRITTED_CASE_VAR_NAME);
    fprintf(ramFile, "ADD #1\n"); codeCursor++;
    STORE_VARIABLE(MEMORY_ARRAY_WRITTED_CASE_VAR_NAME);
}

void creerTableau(char *identificateur) {
    /**
     * @brief On crée la variable 'tab'
     * La valeur de 'tab' est l'indice de la case disponible (stocké à l'emplacement MEMORY_ARRAY_WRITTED_CASE_VAR_NAME)
     * 
     */
    // La taille du tableau est stocké à l'emplacement $stackCursor

    // créer variable tab
    ts_ajouter_id(table, identificateur);

    int id = ts_retrouver_id(table, MEMORY_ARRAY_WRITTED_CASE_VAR_NAME);

    // on initialise la variable tab à la case ou on
    // peut écrire
    LOAD_VARIABLE(MEMORY_ARRAY_WRITTED_CASE_VAR_NAME);
    STORE_VARIABLE(identificateur);

    LOAD_MEM(-1); // chargement de la taille
    JUMZ(+9);
    printf("%d:\tSUB #1\n", codeCursor);
    fprintf(ramFile, "SUB #1\n"); codeCursor++;
    STORE(-1);
    stackCursor--;
    LOAD_VALUE(0);
    printf("%d:\tSTORE @%d\n", codeCursor, id);
    fprintf(ramFile, "STORE @%d\n", id); codeCursor++;
    increaseMemoryVariableSize();
    JUMP(-9);

    /**
    Init
    créer variable addrTableauEcriture (ligne memoire 20)
    addrTableauEcriture = 40;

    -------------------------------------

    ACC = 20; // taille du tableau demandé
    STORE 5; // On stocke momentanément la taille du tableau demandé

    créer variable tab (ligne mémoire 21)
    tab = addrTableauEcriture

    load 5; // on charge la taille demandée
    tq ACC faire:
        LOAD 0;
        STORE @(tab + ACC);

    */


}

void LOAD_VALUE(int n) {
    /**
     * @brief Charge la valeur n dans l'accumulateur
     * 
     */
    fprintf(ramFile, "LOAD #%d\n", n);
    printf("%d:\tLOAD #%d\n", codeCursor, n);
    codeCursor++;
}

void LOAD_MEM(int memoryLine) {
    /**
     * @brief Charge la valeur à la ligne de mémoire stackCursor + memoryLine
     * 
     */
    fprintf(ramFile, "LOAD %d\n", stackCursor + memoryLine);
    printf("%d:\tLOAD %d\n", codeCursor, stackCursor + memoryLine);
    codeCursor++;
}

void LOAD_VARIABLE(char *identificateur) {
    /**
     * @brief Charge la valeur de l'identificateur
     * 
     */
    int id = ts_retrouver_id(table, identificateur);
    fprintf(ramFile, "LOAD %d\n", id);
    printf("%d:\tLOAD %d\n", codeCursor, id);
    codeCursor++;
}

void JUMP(int codeLine) {
    /**
     * @brief Effectue un saut à l'instruction codeCursor + codeLine
     * 
     */
    fprintf(ramFile, "JUMP %d\n", codeCursor + codeLine);
    printf("%d:\tJUMP %d\n", codeCursor, codeCursor + codeLine);
    codeCursor++;
}

void JUMZ(int codeLine) {
    /**
     * @brief Si la valeur de l'ACC == 0, alors faire un
     * saut à la ligne codeCursor + codeLine
     * 
     */
    fprintf(ramFile, "JUMZ %d\n", codeCursor + codeLine);
    printf("%d:\tJUMZ %d\n", codeCursor, codeCursor + codeLine);
    codeCursor++;
}

void JUMG(int codeLine) {
    /**
     * @brief Si la valeur de l'ACC > 0, alors faire un
     * saut à la ligne codeCursor + codeLine
     * 
     */
    fprintf(ramFile, "JUMG %d\n", codeCursor + codeLine);
    printf("%d:\tJUMG %d\n", codeCursor, codeCursor + codeLine);
    codeCursor++;
}

void JUML(int codeLine) {
    /**
     * @brief Si la valeur de l'ACC < 0, alors faire un
     * saut à la ligne codeCursor + codeLine
     * 
     */
    fprintf(ramFile, "JUML %d\n", codeCursor + codeLine);
    printf("%d:\tJUML %d\n", codeCursor, codeCursor + codeLine);
    codeCursor++;
}

void STORE(int memoryLine) {
    /**
     * @brief Enregistre la valeur de l'ACC à la case stackCursor + memoryLine
     * 
     */
    fprintf(ramFile, "STORE %d\n", stackCursor + memoryLine);
    printf("%d:\tSTORE %d\n", codeCursor, stackCursor + memoryLine);
    codeCursor++;
    stackCursor++;
}

void STORE_VARIABLE(char *identificateur) {
    /**
     * @brief Enregistre la valeur de l'ACC à la case prévu pour
     * l'identificateur
     * 
     */
    int id = ts_retrouver_id(table, identificateur);
    fprintf(ramFile, "STORE %d\n", id);
    printf("%d:\tSTORE %d\n", codeCursor, id);
    codeCursor++;
}

void ADD(int memoryLine) {
    /**
     * @brief Additionne la valeur à la ligne stackCursor + memoryLine à l'ACC
     * 
     */
    fprintf(ramFile, "ADD %d\n", stackCursor + memoryLine);
    printf("%d:\tADD %d\n", codeCursor, stackCursor + memoryLine);
    codeCursor++;
}

void SUB(int memoryLine) {
    /**
     * @brief Soustrait la valeur à la ligne stackCursor + memoryLine à l'ACC
     * 
     */
    fprintf(ramFile, "SUB %d\n", stackCursor + memoryLine);
    printf("%d:\tSUB %d\n", codeCursor, stackCursor + memoryLine);
    codeCursor++;
}

void MUL(int memoryLine) {
    /**
     * @brief Multiplie la valeur à la ligne stackCursor + memoryLine à l'ACC
     * 
     */
    fprintf(ramFile, "MUL %d\n", stackCursor + memoryLine);
    printf("%d:\tMUL %d\n", codeCursor, stackCursor + memoryLine);
    codeCursor++;
}

void MUL_VALUE(int value) {
    fprintf(ramFile, "MUL #%d\n", value);
    printf("%d:\tMUL %d\n", codeCursor, value);
    codeCursor++;
}

void DIVI(int memoryLine) {
    /**
     * @brief Divise la valeur à la ligne stackCursor + memoryLine à l'ACC
     * 
     */
    fprintf(ramFile, "DIV %d\n", stackCursor + memoryLine);
    printf("%d:\tDIV %d\n", codeCursor, stackCursor + memoryLine);
    codeCursor++;
}

void MOD(int memoryLine) {
    /**
     * @brief Fait le modulo la valeur à la ligne stackCursor + memoryLine à l'ACC
     * 
     */
    fprintf(ramFile, "MOD %d\n", stackCursor + memoryLine);
    printf("%d:\tMOD %d\n", codeCursor, stackCursor + memoryLine);
    codeCursor++;
}

void WRITE() {
    /**
     * @brief Ecrit dans la bande de sortie la valeur contenue
     * dans l'ACC
     * 
     */
    fprintf(ramFile, "WRITE\n");
    printf("%d:\tWRITE\n", codeCursor);
    codeCursor++;
}

void READ() {
    /**
     * @brief Lis dans la bande d'entrée et met
     * la valeur dans l'ACC
     * 
     */
    fprintf(ramFile, "READ\n");
    printf("%d:\tREAD\n", codeCursor);
    codeCursor++;
}

void increaseCodeLine() {
    codeCursor++;
}

void setStackCursor(int n) {
    printf("Stackcursor: %d --> %d\n", stackCursor, n);
    stackCursor = n;
}

void decrementStackCursor(int n) {
    /**
     * @brief Diminue la valeur de stackCursor.
     * Utilisé lorsque on sait que l'on a plus
     * besoin de valeurs précédentes dans la
     * mémoire.
     * 
     */
    setStackCursor(stackCursor - n);
}

void resetStackCursor() {
    setStackCursor(1);
}

int getCurrentLineCode() {
    /**
     * @brief Renvoie la ligne de code actuelle.
     * 
     */
    return codeCursor;
}

int getCurrentStackCursor() {
    return stackCursor;
}

int addID(char *identificateur) {
    return ts_ajouter_id(table, identificateur);
}

int getID(char *identificateur) {
    return ts_retrouver_id(table, identificateur);
}