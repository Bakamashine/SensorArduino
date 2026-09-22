#include "page.h"

int Page::currentPage = MAIN;

int Page::getCurrentPage() {
  return currentPage;
}

void Page::setCurrentPage(int page) {
  currentPage = page;
}