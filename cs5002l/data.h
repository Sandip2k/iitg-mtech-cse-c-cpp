#ifndef DATA_H
#define DATA_H

// Simple struct Data for Satellite Data Demonstration
typedef struct Data {
    int value;
} Data;

Data *createNewData(int value);
void editDataValue(Data *data, int newValue);
void deleteData(Data *data);

#endif