#include "page.h"

int Page::currentPage = MAIN_PAGE;

int Page::getCurrentPage()
{
  return currentPage;
}

void Page::setCurrentPage(int page)
{
  currentPage = page;
}