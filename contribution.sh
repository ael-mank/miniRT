#!/bin/bash

# Ensure the script exits if any command fails
set -e

# Get the current branch name
current_branch=$(git branch --show-current)

# Define the default branch (usually 'main' or 'master')
default_branch="master"

# Create a new branch from the current branch
new_branch="fake-contributions-$(date +%s)"
git checkout -b $new_branch

# Rebase the new branch onto the default branch
git rebase $default_branch

# Switch to the default branch
git checkout $default_branch

# Merge the new branch into the default branch
git merge $new_branch

# Push the changes to the remote repository
git push origin $default_branch

# Delete the new branch locally
git branch -d $new_branch

# Optionally, delete the new branch on the remote repository
git push origin --delete $new_branch

# Switch back to the original branch
git checkout $current_branch

echo "Fake contributions have been pushed to the default branch."