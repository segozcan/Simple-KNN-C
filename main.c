#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct fish{
    float coordinates[2];
    int type; //  1 is salmon 0 is seabass, -1 if unknown
    struct fish* nearest_neigbors;
    float distance;
} Fish ;

Fish* newFish(float* coordinates){
    Fish* new_fish = (Fish*)malloc(sizeof(Fish));
    new_fish->coordinates[0]=*coordinates;
    new_fish->coordinates[1]=*(coordinates+1);
    new_fish->type=-1;
    new_fish->nearest_neigbors=NULL;
    new_fish->distance =0.0;
    return new_fish;
}


Fish* getDataSet(int length){
    
    int i = 0;
    float coordinates[2]={0.0,0.0}; 
    Fish* dataSet = (Fish*)malloc(sizeof(Fish)*length);

    for(i=0;i<length;i++){
        
        Fish* fish = newFish(coordinates);
        scanf("%f %f %d", &(fish->coordinates), &(fish->coordinates)+1,&(fish->type));
        dataSet[i].coordinates[0] = fish->coordinates[0];
        dataSet[i].coordinates[1] = fish->coordinates[1];
        dataSet[i].type = fish->type;
    }

    return dataSet;
}

void detectDistance(Fish* subject, Fish* dataset, int length) {

    subject->nearest_neigbors = (Fish *) malloc(sizeof(Fish) * 3);
    int k = 0;
    float distance = 0;
    float pivot;
    //Get the distances of all train fish to subject
    for (k = 0; k < length ; k++) {
        distance = sqrt(pow(dataset[k].coordinates[0] - subject->coordinates[0], 2)
                        + pow(dataset[k].coordinates[1] - subject->coordinates[1], 2));
        dataset[k].distance = distance;
    }
}

Fish * sortDistance(Fish* dataset, int length){

    int i = 0;
    int j =0 ;
    for (i=0 ; i < length -1 ; i++ ){

        for( j =0; j< length - i -1; j++){

            if(dataset[i].distance >= dataset[i+1].distance ){
                Fish temp = dataset[i+1];
                dataset[i+1] = dataset[i];
                dataset[i] = temp;
            }
        }
    }
}

int detectType(Fish* subject, Fish * dataset){

    int salmonCount=0;
    int seabassCount =0;

    int i =0;
    for(i=0; i< 3;i++ ){
        if(dataset[i].type ==1){
            salmonCount++;
        }
        else if(dataset[i].type==0){
            seabassCount++;
        }
    }

    if(seabassCount>salmonCount){
        subject->type= 0;
    }else{
        subject->type=1;
    }
    printf("Type: %d", subject->type);
    return subject->type;
}

int main(){
    int length;
    int type;
    float coordinates[2];
    scanf("%d \n", &length );
    scanf("%f %f\n",coordinates+0, coordinates+1 );
    Fish *subject = newFish(coordinates);
    Fish* dataset = getDataSet(length);
    detectDistance(subject, dataset, length);
    sortDistance(dataset, length);
    type = detectType(subject, dataset);

    return 0;
}