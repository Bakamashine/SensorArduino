#pragma once

// main router
enum PageId
{
  MAIN_PAGE,
  SELECT_SETTINGS,
};

class Page
{
private:
  static int currentPage; // one of PageId
public:
  static int getCurrentPage();
  static void setCurrentPage(int page);
};