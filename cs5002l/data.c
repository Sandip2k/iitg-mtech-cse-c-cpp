#include <stdio.h>
#include <stdlib.h>
#include "data.h"

Data *createNewData(int value) {
    Data *newData = (Data *) malloc(sizeof(Data));
    newData->value = value;
    return newData;
}

void editDataValue(Data *data, int newValue) {
    data->value = newValue;
}

void deleteData(Data *data) {
    free(data);
}
