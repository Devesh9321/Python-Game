
import pygame
import os
import random

##################################################

##################################################
import pygame
import os


class Spaceship():
    def __init__(self, width, height):
        self.img = pygame.image.load(os.path.join('./asserts', 'ship.png'))
        self.pos = pygame.Vector2(width, height)


class FiredBullets():
    def __init__(self, width, height, scr_hight):
        self.scr_hight = scr_hight
        self.isblast = False
        self.img = pygame.image.load(
            os.path.join('./asserts', 'fired_bullet.png'))
        self.pos = pygame.Vector2(width, height)

    def update(self):
        if self.pos.y > self.scr_hight and not self.isblast:
            self.pos.y -= 2
        else:
            return False

        return True

    def checkblast(self, list_metoroid):
        for ele in list_metoroid:
            if (ele.pos.x == self.pos.x or ele.pos.x + 10 == self.pos.x or ele.pos.x + 20 == self.pos.x) and ele.pos.y + 48 == self.pos.y:
                list_metoroid.remove(ele)
                return True
        return False


class Metoroied():
    def __init__(self, width, height, hard: bool, scr_hight):
        self.scr_hight = scr_hight
        if hard:
            self.img = pygame.image.load(
                os.path.join('./asserts', 'metoroid.png'))
        else:
            self.img = pygame.image.load(
                os.path.join('./asserts', 'metoroid2.png'))
        self.pos = pygame.Vector2(width, height)

    def update(self):
        if self.pos.y < self.scr_hight:
            self.pos.y += 2
            return True
        return False


def push_in_sorted_list(list_name, value):
    # Find the insertion index using binary search
    left, right = 0, len(list_name) - 1
    while left <= right:
        mid = (left + right) // 2
        if list_name[mid].pos.x < value.pos.x:
            left = mid + 1
        else:
            right = mid - 1

    list_name.insert(left, value)


def text_screen(text, color, x, y):
    screen_text = font.render(text, True, color)
    screen.blit(screen_text, [x, y])


def exit_screen(score):
    screen.fill((197, 235, 170))
    text_screen(f'Game Over', (55, 66, 89), 10, 300)
    text_screen(f'Score : { score }', (55, 66, 89), 10, 400)
    pass


# pygame setup
pygame.init()
screen = pygame.display.set_mode((400, 720))
pygame.display.set_caption("Space Fight ")
font = pygame.font.SysFont(None, 55)
clock = pygame.time.Clock()

# Background
background = pygame.image.load('./asserts/background.png')
bg_pos = pygame.Vector2(0, 0)

# Settring object and collector of object
spaceship = Spaceship(screen.get_width()/2, screen.get_height()-100)
fired_bullet = list()
metoroied_shower = list()

# blast
blast_img = pygame.image.load(os.path.join('./asserts', 'blast.png'))
blast_pos = pygame.Vector2(-1, -1)

# Start the game


def gameloop():
    running = True
    gameOver = False
    dt = 0
    Score = 0
    while running:
        # pygame.QUIT event means the user clicked X to close your window
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        if gameOver:
            exit_screen(score=Score)
        else:
            
            # fill the screen with Background image     # screen.fill((8, 28, 59))
            screen.blit(background, bg_pos)

            # Initialize the spaceship on screen
            screen.blit(spaceship.img, spaceship.pos)

            # Setting ship position base on key pressed
            keys = pygame.key.get_pressed()
            if keys[pygame.K_UP]:
                spaceship.pos.y -= 10
            if keys[pygame.K_DOWN]:
                spaceship.pos.y += 10
            if keys[pygame.K_LEFT] and spaceship.pos.x > 0:
                spaceship.pos.x -= 5
            if keys[pygame.K_RIGHT] and spaceship.pos.x < screen.get_width() - 60:
                spaceship.pos.x += 5

            # bullet fired when `space key` is pressed
            if keys[pygame.K_SPACE]:
                bullet = FiredBullets(
                    spaceship.pos.x + 30, spaceship.pos.y, 30)
                push_in_sorted_list(fired_bullet, bullet)
                print(len(fired_bullet), ' ', end=' ')
                # fired_bullet.append(bullet)

            # Generating the Metoroieds
            if len(metoroied_shower) <= 3:
                metoroied = Metoroied(int(random.randint(4, 35)*10),
                                    10, 0, screen.get_height() - 20)
                push_in_sorted_list(metoroied_shower, metoroied)
                # metoroied_shower.append(metoroied)

            # Move the Generated Bullet towards enamy
            for eleb in fired_bullet:
                if eleb.update():
                    screen.blit(eleb.img, eleb.pos)
                else:
                    fired_bullet.remove(eleb)

                # if metoroied_shower[0].pos.x == eleb.pos.x and metoroied_shower[0].pos.y + 48 == eleb.pos.y:
                if eleb.checkblast(metoroied_shower):
                    Score += 1
                    blast_pos = eleb.pos
                    screen.blit(blast_img, blast_pos)
                    fired_bullet.remove(eleb)

            # Move the Generated metoroied towards ship
            for elem in metoroied_shower:
                if elem.update():
                    screen.blit(elem.img, elem.pos)
                else:
                    metoroied_shower.remove(elem)
                if elem.pos.x + 10 == spaceship.pos.x + 30 and elem.pos.y + 40 == spaceship.pos.y:
                    gameOver = True
            # Display the Score on Screen
            text_screen(f'Score : {Score}', (255, 0, 0), 10, 20)

        # flip() the display to put your work on screen  # pygame.display.flip()
        pygame.display.update()

        # limits FPS to 60  # dt is delta time in seconds since last frame, used for framerate-
        dt = clock.tick(10) / 1000
            
    pygame.quit()


if __name__ == '__main__':
    gameloop()
