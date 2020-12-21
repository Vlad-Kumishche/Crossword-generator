#include "Attr.h"

bool Attr::is_empty() const { return (has_blanks && !has_letters); }
bool Attr::is_partial() const { return (has_blanks && has_letters); }
bool Attr::is_full() const { return (!has_blanks && has_letters); }