//INCLUSIÓ DE LLIBRERIES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//INCLUSIÓ DE LINKEDLIST.H
#include "linkedlist.h" 

//DEFINICIÓ DE CONSTANTS
#define MAX_CHAR     50

//CREACIÓ TYPEDEF ON GUARDEM INFO PRINCIPAL DEL GRUP DE MALALTIES
typedef struct {
    char nom_disease[MAX_CHAR];
    int num_simptomes;
    LinkedList simptoma;
} Disease;

//CREACIÓ TYPEDEF ON GUARDEM SIMPTOMES
typedef struct {
    char disease[MAX_CHAR];
    char symptom[MAX_CHAR];
    int relevance;
} FileDisease;

//CREACIÓ TYPEDEF ON GUARDEM VARIABLES DE SUBSITUCIÓ PER NO DESORDENAR EL FITXER
typedef struct {
    char symptom[300];
    char buffer[MAX_CHAR];
} Detector;

/*********************************************** *
* @Finalitat: TROBAR NOMBRE DE MALALTIES I GUARDER DADES DEL FITXER DE TEXT ALS TYPEDEF
* @Paràmetres: Char nom_fitxer[], Disease **disease, int *num_diseases, Element ele
* @Retorn: --
* ************************************************/
void fitxerDisease(char nom_fitxer[], Disease **disease, int *num_diseases, Element ele) {

    FILE *fd;
    int i, rellevancia, cont;
    char info[MAX_CHAR];

    rellevancia = 0;
    cont = 0;
    i = 0;

    fd = fopen(nom_fitxer, "r");

    if (fd == NULL) {

        printf("\nERROR: Diseases file not found");
        *num_diseases = 0;

    } else {

        //RESERVA MEMORIA ILIMITADA PER GUARDAR LES MALALTIES
        fscanf(fd, "%d\n", num_diseases);
        *disease = (Disease *) malloc(20 * sizeof(Disease));

        while (!feof(fd)) {

            

            fgets((*disease)[cont].nom_disease, MAX_CHAR, fd);
            (*disease)[cont].nom_disease[strlen((*disease)[cont].nom_disease) - 1] = '\0';

            fscanf(fd, "%d\n", &(*disease)[cont].num_simptomes);
            (*disease)[cont].simptoma = LINKEDLIST_create();

            for (i = 0; i < (*disease)[cont].num_simptomes; i++) {

                fgets(info, MAX_CHAR, fd);
                info[strlen(info) - 1] = '\0';

                char copiar_simptoma[30];
                int surt = 0;
                int cad;

                for (cad = 0; cad < strlen(info) && surt == 0; cad++) {

                    if (info[cad] != '(') {

                        copiar_simptoma[cad] = info[cad];

                    } 
                    
                    else {
                        surt = 1;
                    }
                }

                cad = cad - 2;
                copiar_simptoma[cad] = '\0';
                strcpy(ele.symptom, copiar_simptoma);
                cad = cad + 2;

                surt = 0;

                rellevancia = atoi(&info[cad]);
                ele.relevance = rellevancia;
                rellevancia = 0;

                LINKEDLIST_add(&((*disease)[cont].simptoma), ele);            
                LINKEDLIST_next(&(*disease)[cont].simptoma);

                for (int neteja = 0; neteja < 50; neteja++) {
                    copiar_simptoma[neteja] = '\0';
                }
                
            }

            cont++;

        }

        fclose(fd);

    }

}

/*********************************************** *
* @Finalitat: OPCIÓ 1 COMPLETA
* @Paràmetres: Disease *disease, int start, Element ele
* @Retorn: --
* ************************************************/
void opcioPrimera(Disease *disease, int start, Element ele) {

    int i, j;

    i = 0;
    j = 0;

    printf ("\nRegistered diseases:\n\n");

    for (i = 0; i < start; i++) {

        printf("%s", disease[i].nom_disease);

        //INICI DE LA LINKEDLIST
        LINKEDLIST_goToHead(&disease[i].simptoma);

        if (disease[i].num_simptomes > 0) {

            printf (" (");

            for (j = 0; j < disease[i].num_simptomes; j++) {

                //AGAFA ELEMENT LINKEDLIST
                Element ele = LINKEDLIST_get(&disease[i].simptoma);

                if (j == 0) {
                    printf("%s#%d", ele.symptom, ele.relevance);

                    //PASSA AL SEGUENT NODE LINKEDLIST
                    LINKEDLIST_next(&disease[i].simptoma);
                }

                else {
                    printf(" | %s#%d", ele.symptom, ele.relevance);

                    //PASSA AL SEGUENT NODE LINKEDLIST
                    LINKEDLIST_next(&disease[i].simptoma);
                }

            }

            printf (")\n");

        }

        //PASSA AL SEGUENT NODE LINKEDLIST
        LINKEDLIST_next(&disease[i].simptoma);

    }

}

/*********************************************** *
* @Finalitat: GUARDER DADES DEL FITXER BINARI ALS TYPEDEF
* @Paràmetres: char fitxer_research[], FileDisease filebin[]
* @Retorn: RETORNA i QUE INDICA SI S'HAN INTRODUIT CORRECTAMENT I HAN ENTRAT LES DADES DEL FITXER RESEARCH
* ************************************************/
int fitxerResearch (char fitxer_research[], FileDisease filebin[]) { 

    FILE* fr;

    int i;

    i = 0;

    fr = fopen(fitxer_research, "rb");

    if (fr == NULL) {
        printf("\nERROR: Research file not found\n");

    }

    else {

        fread(&filebin[i], sizeof(FileDisease), 1, fr);
        
        while (!feof(fr)) {
            
            i++;
            fread(&filebin[i], sizeof(FileDisease), 1, fr);
        }

    }

    fclose(fr);

    return i;
}

/*********************************************** *
* @Finalitat: OPCIÓ 2 COMPLETA
* @Paràmetres: int validate, int start, Disease *disease, FileDisease filebin[], Element ele)
* @Retorn: --
* ************************************************/
void opcioSegona(int validate, int start, Disease *disease, FileDisease filebin[], Element ele) { 

    int repetit_malaltia, j, k, i, repetit_simptoma, simptomes_actualitzats, simptomes_afegits, malalties_ignorades;

    repetit_malaltia = 0;
    repetit_simptoma = 0;
    simptomes_actualitzats = 0;
    simptomes_afegits = 0;
    malalties_ignorades = 0;
    i = 0;
    j = 0;
    k = 0;

    if (validate != 0) {

        for (i=0; i < validate; i++) {

            for (j=0; j <= start - 1 && repetit_malaltia == 0; j++) {

                if (strcmp(disease[j].nom_disease, filebin[i].disease) == 0) {
                
                    repetit_malaltia = 1;
                
                }
            }

            if (repetit_malaltia == 1) {

                int up;
                up = 0;

                for (j=0; j < start; j++) {
                    
                    if (strcmp(filebin[i].disease, disease[j].nom_disease) == 0) {

                        //ENS SITUEM AL PRIMER ELEMENT LINKEDLIST
                        LINKEDLIST_goToHead(&disease[j].simptoma);

                        for (k = 0; k < disease[j].num_simptomes; k++) {

                            //AGAFEM ELEMENT LINKETLIST
                            ele = LINKEDLIST_get(&disease[j].simptoma);

                            if ((strcmp(filebin[i].symptom, ele.symptom) == 0) && up == 0) {

                                repetit_simptoma = 1;

                                if (filebin[i].relevance != ele.relevance) {
                                    simptomes_actualitzats++;
                                    up = 1;
                                    ele.relevance = filebin[i].relevance;
                                }

                                //BORREM ELEMENT LINKEDLIST
                                LINKEDLIST_remove(&disease[j].simptoma);
                                strcpy(ele.symptom, filebin[i].symptom);

                                //AFEGIM ELEMENT LINKEDLIST
                                LINKEDLIST_add(&disease[j].simptoma, ele);

                            }

                            //PASSEM AL SEGUENT NODE LINKEDLIST
                            LINKEDLIST_next(&disease[j].simptoma);

                        }

                        if (repetit_simptoma == 0) {

                            strcpy(ele.symptom, filebin[i].symptom);
                            ele.relevance = filebin[i].relevance;
                            disease[j].num_simptomes++;

                            //AFEGIM ELEMENT LINKEDLIST
                            LINKEDLIST_add (&disease[j].simptoma, ele);

                            simptomes_afegits++; 
                        }

                    }  
                }
            }

            else {
                malalties_ignorades++;
            }



            repetit_malaltia = 0;
            repetit_simptoma = 0;

        }

        printf ("\n%d diseases ignored", malalties_ignorades);
        printf ("\n%d symptoms updated", simptomes_actualitzats);
        printf ("\n%d symptoms added\n", simptomes_afegits);

    }
}

/*********************************************** *
* @Finalitat: POSAR L'ORDRE DE GRAN A PETIT A L'OPCIÓ 3
* @Paràmetres: int *sumador_rellevancia, Disease *disease, int start, Detector *detect
* @Retorn: --
* ************************************************/
void miOrdenacion(int *sumador_rellevancia, Disease *disease, int start, Detector *detect) { 
    
    int i, j, max, guardar;
    char guarchar[MAX_CHAR];

    i = 0;
    j = 0;
    max = 0;

    if (sumador_rellevancia != NULL && disease != NULL && detect != NULL) {

        for (i=0; i < start; i++) {

            if (strcmp(disease[i].nom_disease, "") != 0) { 
                strcpy(detect[i].buffer, disease[i].nom_disease);
            }
        }
        
        for (i = 0; i + 1 < start; i++) {

            max = start - i;

            for (j = 0; j + 1 < max; j++) {

                if (sumador_rellevancia[j] < sumador_rellevancia[j+1]) {

                    guardar = sumador_rellevancia[j];
                    strcpy (guarchar, detect[j].buffer);
                    sumador_rellevancia[j] = sumador_rellevancia[j+1];
                    strcpy (detect[j].buffer, detect[j+1].buffer);
                    sumador_rellevancia[j+1] = guardar;
                    strcpy (detect[j+1].buffer, guarchar);

                }

            }
        }
    }
}

/*********************************************** *
* @Finalitat: MOSTRA EL MENU I GUARDA L'OPCIÓ INTRODUIDA PER L'USUARI
* @Paràmetres: --
* @Retorn: RETORNA L'OPCIÓ QUE HA DIT LUSUARI
* ************************************************/
char mostraMenu() {

    char opcio[50];

    printf("\n1. Show diseases | 2. Load research advances | 3. Help me! | 4. Quit\n");

    printf("\nEnter option: ");
    fgets(opcio, 50, stdin);
    opcio[strlen(opcio)-1] = '\0';

    return opcio[0];

}

//MAIN
int main () {
    
    //NOMBREM VARIABLES
    Disease *disease = NULL;
    FileDisease filebin[50];
    Detector detect[30];
    Element ele;

    char nom_fitxer[50], opcio[50], fitxer_research[50], cadena_simptomes[100];
    int start, i, j, k, validate, sumador_rellevancia[20];
    int cont_sym, detected;

    //INICIALITZEM VARIABLES
    i = 0;
    validate = 0;
    detected = 0;
    j = 0;
    k = 0;
    cont_sym = 0;
    sumador_rellevancia[0] = 0;
    
    printf("Enter diseases file name: ");
    fgets (nom_fitxer, 50, stdin);
    nom_fitxer[strlen(nom_fitxer) - 1] = '\0';
    
    //LLEGIM FITXER DE TEXT
    fitxerDisease(nom_fitxer, &disease, &start, ele);

    //COMENÇA EL PROGRAMA
    if (start != 0) {

        printf("Welcome to myDoctor!\n");

        while (start != 0) {
            
            opcio[0] = mostraMenu();
            char option = opcio[0];

            //OPCIO 1
            if (option == '1'){

                opcioPrimera (disease, start, ele);

            }

            //OPCIO 2
            if (option == '2') {
                
                //INTRODUCCIÓ DELS SIMPTOMES I TREURE EL \0 DEL FINAL
                printf ("Enter research file name: ");
                fgets (fitxer_research, 50, stdin);
                fitxer_research[strlen(fitxer_research) - 1] = '\0';

                //EXECUCIÓ DE LES FUNCIONS
                validate = fitxerResearch (fitxer_research, filebin);

                opcioSegona (validate, start, disease, filebin, ele);
                
            }
            
            //OPCIO 3
            if (option == '3') {
                
                //INTRODUCCIÓ DELS SIMPTOMES I TREURE EL \0 DEL FINAL
                printf ("Enter your symptoms: ");
                fgets(cadena_simptomes, 100, stdin);
                cadena_simptomes[strlen(cadena_simptomes) - 1] = '\0';

                k = 0;
                j = 0;
                
                //SEPAREM LA CADENA DE CARACTES ANOMENADA CADENA_SIMPTOMES QUAN HI HAGI EL SIMBOL +, GUARDEM CADA SIMPTOMA X SEPARAT AL TYPEDEF DETECT.SYMPTOM
                for (i = 0; i < strlen(cadena_simptomes); i++) {

                    if (cadena_simptomes[i] != '+') {
                        
                        detect[j].symptom[k] = cadena_simptomes[i];
                        k++;

                    }

                    else {
                        detect[j].symptom[k] = '\0';
                        k = 0;
                        j++;

                    }
                }
                detect[j].symptom[k] = '\0';

                Symptom simptoma;

                //COMPAREM ELS SIMPTOMES INTRODUITS AMB ELS JA GUARDATS INICIALMENT DE CADA MALALTIA, SI COINCIDEIXEN, LI SUMEM A LA MALALTIA EL NUMERO DE RELLEVANCIA DEL SIMPTOMA. AIXO
                //HO FEM AMB CADA MALALTIA I SIMPTOMA, PER AIXO EL BUCLE
                for (i=0; i <= j; i++) {

                    for (k=0; k < start; k++) {

                        LinkedList ele = disease[k].simptoma;

                        //ANEM AL PRINCIPI DE LA LINKEDLIST
                        LINKEDLIST_goToHead(&ele);

                        for (cont_sym = 0; cont_sym < disease[k].num_simptomes; cont_sym++) {
                            
                            //AGAFEM ELEMENT LINKEDLIST
                            simptoma = LINKEDLIST_get(&ele);

                            if (strcmp (detect[i].symptom, simptoma.symptom) == 0) {
                                sumador_rellevancia[k] = sumador_rellevancia[k] + simptoma.relevance;
                                detected = 1;
                            }

                            //PASSEM AL SEGUENT NODE DE LA LINKEDLIST
                            LINKEDLIST_next(&ele);
                        }

                    }
                    
                }

                //LLISTAT GENERAT UTILITZANT L'ESTRUCTURA DE DADES DINÀMIQUES DEL FITXERDISEASE
                //SI SHA INTRODUIT ALGUNA MALALTIA, LA MOSTREM, AMB EL SEU NOM I EL NOMBRE TOTAL DE RELLEVANCIA SUMAT
                if (detected == 1) {

                    printf ("\nMost probable diseases: \n");
                    
                    //ORDENA DE GRAN A PETIT LES MALALTIES
                    miOrdenacion (sumador_rellevancia, disease, start, detect);

                    //MOSTRE TOTES LES MALALTIES I EL SUMADOR DE RELLEVANCIES
                    for (i=0; i <= start; i++) {

                        if (sumador_rellevancia[i] > 0) {

                            printf ("Total relevance %d: %s\n", sumador_rellevancia[i], detect[i].buffer);
                            sumador_rellevancia[i] = 0;

                        }
                        
                    }
                }

                //QUAN NO S'HA INTRODUIT CAP MALALTIA A LOPCIO 3 ES MOSTRA L'ERROR
                else {
                    printf ("\nNo diseases found!\n");
                }

                //NETEJA EL TYPEDEF DETECT, CADENA_SIMPTOMES I SUMADOR_RELLEVANCIA PER QUAN VULGUEM TORNAR A FER LOPCIO 3
                for (i=0; i < 50; i++) {

                    sumador_rellevancia[i] = 0;

                }

                for (i = 0; i < strlen(cadena_simptomes); i++) {
                    cadena_simptomes[i] = '\0';
                }

                for (i = 0; i < 30; i++) {
                    for (j = 0; j < 50; j++) {
                        detect[i].symptom[j] = '\0';
                    }
                }

                //NETEJA DE VARIABLES O INICIALITZACIÓ
                i = 0;
                k = 0;
                j = 0;
                cont_sym = 0;
                detected = 0;

            }

            //OPCIO 4
            if (option == '4') {

                //MISSATGE DE DESPEDIDA
                printf ("\nStay healthy!");

                //LLIBERACIÓ DE MEMORIA
                for (i = 0; i < start + 1; i++) {

                    //DESTRUIM LA LINKEDLIST I LLIBEREM LA MEMORIA
                    LINKEDLIST_destroy(&disease[i].simptoma);
                }
                free(disease);

                start = 0;
            }

            //SI SINTRODUEIX UNA OPCIO DIFERENT A LES QUE POSSIBIdLITA EL MENU, DONA ERROR I TORNA A ENSENYAR EL MENU
            if ((option != '1') && (option != '2') && (option != '3') && (option != '4')) {
                
                //MISSATGE D'ERROR
                printf ("\nERROR: Wrong option\n");
            }
        }

    }

    //ACABA EL PROGRAMA
    return 0;
}