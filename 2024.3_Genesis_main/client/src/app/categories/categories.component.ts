import { HttpClient } from '@angular/common/http';
import { Component } from '@angular/core';
import { RouterLink } from '@angular/router';
import { SpinnerComponent } from '../spinner/spinner.component';

@Component({
  selector: 'app-categories',
  standalone: true,
  imports: [RouterLink, SpinnerComponent],
  templateUrl: './categories.component.html',
  styleUrl: './categories.component.scss'
})
export class CategoriesComponent {
  categories: any = []

  isLoading: boolean = false;

  constructor(private http: HttpClient) { }

  ngOnInit() {
    this.isLoading = true;
    this.http.get('http://localhost:8000/categories').subscribe(data => {
      this.categories = data
      this.isLoading = false;
    })
  }
}
