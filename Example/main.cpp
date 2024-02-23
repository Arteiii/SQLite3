#include "pch.h"

int
main()
{
  // Smart pointer for automatic resource management
  // std::unique_ptr is used for automatic memory management.
  // It ensures that the sqlite3 pointer is properly released when it goes out
  // of scope.
  std::unique_ptr<sqlite3, decltype(&sqlite3_close)> db(nullptr,
                                                        &sqlite3_close);
  char* errMsg = nullptr;

  // Create a raw pointer to sqlite3
  // A raw pointer is initially used to interact with functions that expect a
  // pointer to a pointer. Later, ownership is transferred to the unique_ptr.
  sqlite3* rawDb = nullptr;

  try {
    // Open a connection to the database
    int rc = sqlite3_open("example.db", &rawDb);

    // Transfer ownership to unique_ptr
    // The ownership of the raw pointer obtained from sqlite3_open is
    // transferred to the unique_ptr. Now, the unique_ptr is responsible for
    // managing the memory.
    db.reset(rawDb);

    if (rc != SQLITE_OK) {
      // Throw an exception if the database cannot be opened
      throw std::runtime_error("Cannot open database: " +
                               std::string(sqlite3_errmsg(db.get())));
    } else {
      std::cout << "Database opened successfully." << std::endl;
    }

    // Create a simple table
    const char* createTableSQL =
      "CREATE TABLE IF NOT EXISTS MyTable (ID INT, Name TEXT);";

    // Execute SQL statement to create a table
    rc = sqlite3_exec(db.get(), createTableSQL, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
      // Throw an exception if the SQL execution fails
      throw std::runtime_error("SQL error: " + std::string(errMsg));
    } else {
      std::cout << "Table created successfully." << std::endl;
    }

    // Insert some data into the table
    const char* insertDataSQL = "INSERT INTO MyTable VALUES (1, 'John');";

    // Execute SQL statement to insert data
    rc = sqlite3_exec(db.get(), insertDataSQL, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
      // Throw an exception if the SQL execution fails
      throw std::runtime_error("SQL error: " + std::string(errMsg));
    } else {
      std::cout << "Data inserted successfully." << std::endl;
    }
  } catch (const std::exception& e) {
    // Catch and handle exceptions
    std::cerr << "Exception: " << e.what() << std::endl;
    if (errMsg != nullptr) {
      sqlite3_free(errMsg);
    }
    return EXIT_FAILURE;
  }

  return 0;
}
