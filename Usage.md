# Startup config

## Set default editor

```yaml
# ~/.config/.note/config.yaml

settings:
    #Change your default editor
    editor: nano
```

## Create a note
``` bash
.note new note_name
```

## Search notes
```bash
.note search multiword query # will match if any word is matched

.note search -a multiword query # will match if all words match

.note search -tc query # Time of creation ordered results (Most recent first)

.note search -tC query # Most recent last
```

## Add existing note to repository
```bash
.note add path/to/note.md # Will copy notes

.note add -l path/to/note.md # symlink notes
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
