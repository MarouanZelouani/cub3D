/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:31:09 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:31:10 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "./libs.h"

typedef struct s_parsed_data
{
  char *north_textures;
  char *south_textures;
  char *west_textures;
  char *east_textures;
  int floor_rgb;
  int ceiling_rgb;
  char **map;
  int x;
  int y;
  char direction;
  int w;
  int h;
} t_parsed_data;

typedef struct s_map_list
{
  char *str;
  struct s_map_list *next;
} t_map_list;

void append_map_list(char *line, t_map_list **head, t_map_list **tail);
int is_a_string(char *str);
int is_an_integer(char *str);
int parse(char *filename, t_parsed_data *data);
int done_parsing_data(t_parsed_data *data);
int rgb(char *str);
void free_data(t_parsed_data *data);
void free_map_list(t_map_list *head);
int check_map_validity(t_map_list *head);
int get_map(t_parsed_data *data, t_map_list *node);
void get_coords(t_parsed_data *data);
int check_file_extension(char *filename, char *extension);
int check_ex(t_parsed_data *data);

int data_p(t_parsed_data *data, char **line, int fd);
int initialize(t_parsed_data *data, char *str, int *fd);
int get_integer(char *str, t_parsed_data *data);
int get_string(char *line, t_parsed_data *data);
int validation(t_parsed_data *data);
int space_checker(t_parsed_data *data);
int zero_checker(t_parsed_data *data);
void trim(t_parsed_data *data);
int get_size(t_map_list *node, int *len, int *rows);
void write_to_map(t_parsed_data *data, t_map_list *node, int i, int *j);
void fill(t_parsed_data *data, int j, int i, int len);
void fill_map(t_parsed_data *data, t_map_list *node, int len);
void	cut(char **str);
#endif // !PARSING_H