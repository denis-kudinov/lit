file(REMOVE_RECURSE
  "libFileWatcher.a"
  "libFileWatcher.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/FileWatcher.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
