#!/bin/bash

# ref1: https://dev.to/jenc/removing-accidentally-committed-files-from-remote-history-3acj
# ref2: https://stackoverflow.com/questions/2100907/how-to-remove-delete-a-large-file-from-commit-history-in-git-repository/2158271#2158271

# context
# 1. we wish to remove a large file from our commit history
# 2. the large filename is bigOops.file
# 3. we are correcting branch main

# steps
####
# 1. run git filter-branch
git filter-branch --prune-empty -d /dev/shm/scratch \
  --index-filter "git rm --cached -f --ignore-unmatch bigOops.file" \
  --tag-name-filter cat -- --all
  
#    if it's bigOops_folder instead of just a file  
git filter-branch --prune-empty -d /dev/shm/scratch \
  --index-filter "git rm --cached -r -f --ignore-unmatch bigOops_folder" \
  --tag-name-filter cat -- --all
  
#    if you've done this before and there's a backup of a previous filter-branch that needs to be purged/overwritten in order to proceed
git filter-branch -f --prune-empty -d /dev/shm/scratch \
  --index-filter "git rm --cached -r -f --ignore-unmatch bigOops_folder" \
  --tag-name-filter cat -- --all
  
#    if we also need to do this on all other branches
git filter-branch -f --prune-empty -d /dev/shm/scratch \
  --index-filter "git rm --cached -r -f --ignore-unmatch bigOops_folder" \
  --tag-name-filter cat -- --all
 
# 2. remove the original commits that existed prior to filter-branch
git update-ref -d refs/originals/refs/heads/main

# 3. expire reflog entries since they aren't relevant anymore
git reflog expire --expire=now --all

# 4. and remove them to reduce git history size
git gc --prune=now

# 5. push changes to remote
git push --force origin main
