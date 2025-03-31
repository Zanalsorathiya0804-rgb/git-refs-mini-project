#include <stdio.h>
#include <git2.h>

void list_refs() {
    git_repository *repo = NULL;
    git_reference_iterator *iter = NULL;
    git_reference *ref = NULL;

    if (git_repository_open(&repo, ".")) {
        printf("Error opening repository.\n");
        return;
    }

    if (git_reference_iterator_new(&iter, repo)) {
        printf("Error creating reference iterator.\n");
        git_repository_free(repo);
        return;
    }

    while (!git_reference_next(&ref, iter)) {
        printf("Ref: %s\n", git_reference_name(ref));
        git_reference_free(ref);
    }

    git_reference_iterator_free(iter);
    git_repository_free(repo);
}

int main() {
    git_libgit2_init();
    printf("Listing all Git references...\n");
    list_refs();
    git_libgit2_shutdown();
    return 0;
}
