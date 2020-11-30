#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <random>

#include "rocksdb/c.h"

#include <unistd.h>  // sysconf() - get CPU count

const char DBPath[] = "./my_db";

int main(int argc, char **argv) {
  rocksdb_t *db;
  rocksdb_backup_engine_t *be;
  rocksdb_options_t *options = rocksdb_options_create();
  // Optimize RocksDB. This is the easiest way to
  // get RocksDB to perform well
  long cpus = sysconf(_SC_NPROCESSORS_ONLN);  // get # of online cores
  rocksdb_options_increase_parallelism(options, (int)(cpus));
  rocksdb_options_optimize_level_style_compaction(options, 0);
  // create the DB if it's not already present
  rocksdb_options_set_create_if_missing(options, 1);

  // open DB
  char *err = NULL;
  db = rocksdb_open(options, DBPath, &err);
  if (err) {
      printf("Failed to open DB: %s\n", err);
      exit(1);
  }

  // Setup RNG
    std::random_device rd;
    std::mt19937_64 e2(rd());
    std::uniform_int_distribution<long long int> dist(std::llround(std::pow(2,64)));

  // Put key-value
  rocksdb_writeoptions_t *writeoptions = rocksdb_writeoptions_create();
  for (int i = 0; i < 7000; i++) {
	char key[11];
    char value[64];
	snprintf(key, 10, "key%d", i);
    snprintf(value, 65, "%lld", dist(e2));
	rocksdb_put(db, writeoptions, key, strlen(key), value, strlen(value) + 1,
                    &err);
        assert(!err);
  }

  // Get value
  /*
  rocksdb_readoptions_t *readoptions = rocksdb_readoptions_create();
  for (int i = 0; i < 7000; i++) {
	size_t len;
	char key[11];
	snprintf(key, 10, "key%d", i);
	char *returned_value =
		rocksdb_get(db, readoptions, key, strlen(key), &len, &err);
    if (err) {
        printf("GET failed: %s\n", err);
        break;
    }
    //printf("Returned value: %s\n", returned_value);
	//assert(strcmp(returned_value, "value") == 0);
	//free(returned_value);
  }
  */

  // cleanup
  rocksdb_writeoptions_destroy(writeoptions);
  //rocksdb_readoptions_destroy(readoptions);
  rocksdb_options_destroy(options);
  rocksdb_close(db);

  return 0;
}
