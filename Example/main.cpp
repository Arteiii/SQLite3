#include "pch.h"

int
main()
{
  sqlite3* db;
  char* errMsg = 0;

  // Open a connection to the database
  int rc = sqlite3_open("example.db", &db);

  if (rc) {
    std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    return rc;
  } else {
    std::cout << "Database opened successfully." << std::endl;
  }

  // Create a simple table
  const char* createTableSQL =
    "CREATE TABLE IF NOT EXISTS MyTable (ID INT, Name TEXT);";

  rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);

  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  } else {
    std::cout << "Table created successfully." << std::endl;
  }

  // Insert some data into the table
  const char* insertDataSQL = "INSERT INTO MyTable VALUES (1, 'John');";

  rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);

  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  } else {
    std::cout << "Data inserted successfully." << std::endl;
  }

  // Close the database
  sqlite3_close(db);

  return 0;
}
