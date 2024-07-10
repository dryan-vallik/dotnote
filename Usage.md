# Startup config

## Set default editor

```
\# ~/.config/.note/config.yaml

editing:
    \#Change your default editor
    editor: "nano"
```

## Create a note
``` bash
.note new
```

## Search notes
```bash
.note search multiword query

.note search -tc query # Time of creation ordered results (Most recent first)

.note search -tC query # Most recent last
```

## Add existing note to repository
```bash
.note add existing path/to/note.md # Will copy notes

.note add existing -l path/to/note.md # symlink notes
```

## Delete existing note in repository
```bash
.note rm note_name

.note rm -qc query # Will delete existing matching query (-q) upon confirmation (-c)

.note rm -t 2024-07-09 # Delete notes older than date (YEAR-MONTH-DAY)

.note rm --last # Delete last created note
```

## Edit note or create a new one if non existing
```bash
.note edit # Defaults to last used or create if first usage

.note edit note_name

.note edit -q query # Edits most recent found match to the query.
```
