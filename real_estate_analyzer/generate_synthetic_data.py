import random
import csv
import os
import datetime
from typing import List, Dict, Any

# Configuration
NUM_RECORDS = 100
OUTPUT_FILE = "synthetic_property_data.csv"

# Lists of possible values
TOWNS = ["Springfield", "Capital City", "Shelbyville", "Ogdenville", "North Haverbrook"]
STATES = ["IL", "NY", "CA", "TX", "FL"]
PROPERTY_TYPES = ["SingleFamily", "Condo", "Apartment"]
SALE_STATUSES = ["Active", "Sold", "Pending"]
STREET_NAMES = ["Main St", "Oak Ave", "Pine Blvd", "Maple Dr", "Cedar Ln", "Elm St", "Washington Ave"]

def generate_random_date(start_date: datetime.date, end_date: datetime.date) -> str:
    """Generate a random date between start_date and end_date."""
    time_between_dates = end_date - start_date
    days_between_dates = time_between_dates.days
    random_days = random.randrange(days_between_dates)
    random_date = start_date + datetime.timedelta(days=random_days)
    return random_date.strftime("%Y-%m-%d")

def generate_address() -> str:
    """Generate a random address."""
    return f"{random.randint(100, 999)} {random.choice(STREET_NAMES)}"

def generate_property_data() -> Dict[str, Any]:
    """Generate random property data."""
    # Random size between 500 and 5000 sq ft
    size = random.randint(500, 5000)
    
    # Random lot size between 1000 and 20000 sq ft
    lot_size = random.randint(1000, 20000)
    
    # Random number of bedrooms between 1 and 6
    number_of_bed = random.randint(1, 6)
    
    # Random number of bathrooms between 1 and 5
    number_of_bath = random.randint(1, 5)
    
    # Random year built between 1950 and 2024
    year_built = random.randint(1950, 2024)
    
    # Random price between $100k and $1.5M, with some correlation to size
    base_price = random.randint(100000, 1500000)
    adjusted_price = int(base_price * (0.7 + 0.6 * size / 5000))
    
    # Random days on market between 1 and 180
    days_on_market = random.randint(1, 180)
    
    # Random listing date within the last year
    today = datetime.date.today()
    one_year_ago = today - datetime.timedelta(days=365)
    listing_date = generate_random_date(one_year_ago, today)
    
    return {
        "Address": generate_address(),
        "Town": random.choice(TOWNS),
        "State": random.choice(STATES),
        "Zip": f"{random.randint(10000, 99999)}",
        "Size": size,
        "LotSize": lot_size,
        "Bedrooms": number_of_bed,
        "Bathrooms": number_of_bath,
        "YearBuilt": year_built,
        "Price": adjusted_price,
        "DaysOnMarket": days_on_market,
        "PropertyType": random.choice(PROPERTY_TYPES),
        "SaleStatus": random.choice(SALE_STATUSES),
        "ListingDate": listing_date
    }

def generate_csv(num_records: int, output_file: str) -> None:
    """Generate a CSV file with random property data."""
    # Define the headers
    headers = [
        "Address", "Town", "State", "Zip", "Size", "LotSize", "Bedrooms", 
        "Bathrooms", "YearBuilt", "Price", "DaysOnMarket", "PropertyType", 
        "SaleStatus", "ListingDate"
    ]
    
    # Generate the data
    data = [generate_property_data() for _ in range(num_records)]
    
    # Write to CSV file
    with open(output_file, 'w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=headers)
        writer.writeheader()
        writer.writerows(data)
    
    print(f"Generated {num_records} records in {output_file}")

if __name__ == "__main__":
    generate_csv(NUM_RECORDS, OUTPUT_FILE)