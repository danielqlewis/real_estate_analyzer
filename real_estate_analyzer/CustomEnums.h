#pragma once

enum class PropertyType {
    SingleFamily,
    Condo,
    Apartment,
};

enum class SaleStatus {
    Active,
    Sold,
    Pending,
};

enum class AverageType {
    Mean,
    Median
};

enum class ProgramState {
    SelectingFullDataset,
    SelectingFirstSubset,
    SelectingSecondSubset,
    RunningAnalysis,
    DisplayingResults,
    Exit
};